import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import * as moment from 'moment';
import { catchError, map, Observable } from 'rxjs';
import { StorageService } from './storage.service';
import { MatDialog } from '@angular/material/dialog';
import { ErrorComponent } from './error/error.component';
const ical = require('ical.js');

export interface Event {
    name: string,
    begin: string,
    end: string
}

@Injectable({
    providedIn: 'root'
})
export class IcalService {

    constructor(private http: HttpClient, private storage: StorageService, private dialog: MatDialog) { }

    get(): Observable<Event[]> | null {
        const url = this.storage.get("ical-url");
        if (url === "") {
            return null;
        }
        const today = [
            moment().set({
                hour: 0,
                minute: 0,
                second: 0,
                millisecond: 0
            }),
            moment().set({
                hour: 23,
                minute: 59,
                second: 59,
                millisecond: 999
            })
        ];
        return this.http.get(url, { responseType: 'text' }).pipe(
            map(text => {
                const calendar = ical.parse(text);
                let events = [];
                for (const vevent of calendar[2]) {
                    if (vevent[0] !== "vevent") continue;
                    events.push({
                        name: vevent[1][5][3],
                        begin: vevent[1][2][3],
                        end: vevent[1][3][3]
                    })
                }
                events = events.filter(event => {
                    const begin = moment(event.begin);
                    return begin.isBetween(today[0], today[1]);
                });
                for (let i = 1; i < events.length; i += 2) {
                    events.splice(i, 0, {
                        name: "Pause",
                        begin: events[i - 1].end,
                        end: events[i].begin
                    });
                }
                return events as Event[];
            }),
            catchError((error, caught) => {
                console.error(error, caught);
                this.dialog.open(ErrorComponent, {
                    data: "The Ical-Url you entered is invalid."
                })
                return [];
            })
        );
    }
}
