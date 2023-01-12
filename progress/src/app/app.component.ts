import { Component, OnInit } from '@angular/core';
import { MatDialog } from '@angular/material/dialog';
import * as moment from 'moment';
import { ErrorComponent } from './error/error.component';
import { IcalService } from './ical.service';
import { Event } from './ical.service';
import { SettingsComponent } from './settings/settings.component';
import { StorageService } from './storage.service';

@Component({
    selector: 'app-root',
    templateUrl: './app.component.html',
    styleUrls: ['./app.component.scss']
})
export class AppComponent implements OnInit {
    whole = 0;
    current = 0;
    wholeFraction = [0, 0];
    currentFraction = [0, 0];
    diameter = 100;
    textSize = 12;
    currentName = "";
    todayString = moment().format("DD.MM.YYYY");
    events: Event[] = [];

    constructor(private icalService: IcalService, private dialog: MatDialog, private storage: StorageService) {}

    setProgress() {
        const today = Number(moment().set({
            hour: 0,
            minute: 0,
            second: 0,
            millisecond: 0
        }).format("x"));
        const now = Number(moment().format("x")) - today;
        const min = Number(moment(this.events[0].begin).format("x")) - today;
        const max = Number(moment(this.events[this.events.length - 1].end).format("x")) - today;
        this.whole = (now - min) / (max - min) * 100;

        const minMin = Math.trunc(min / 60000);
        let nowMin = Math.trunc(now / 60000) - minMin;
        let maxMin = Math.trunc(max / 60000) - minMin;
        if (maxMin % nowMin === 0) {
            maxMin /= nowMin;
            nowMin = 1;
        } else {
            for (let i = 2; i < nowMin / 2; i++) {
                while (nowMin % i === 0 && maxMin % i === 0) {
                    nowMin /= i;
                    maxMin /= i;
                }
            }
        }
        this.wholeFraction = [nowMin, maxMin];

        for (let i = 0; i < this.events.length; i++) {
            const sMin = Number(moment(this.events[i].begin).format("x")) - today;
            const sMax = Number(moment(this.events[i].end).format("x")) - today;
            if (sMin <= now && sMax >= now) {
                this.current = (now - sMin) / (sMax - sMin) * 100;
                this.currentName = this.events[i].name.replace(/\/\/.*/, "").trim();
                const minMin = Math.trunc(sMin / 60000);
                let nowMin = Math.trunc(now / 60000) - minMin;
                let maxMin = Math.trunc(sMax / 60000) - minMin;
                if (maxMin % nowMin === 0) {
                    maxMin /= nowMin;
                    nowMin = 1;
                } else {
                    for (let i = 2; i < nowMin / 2; i++) {
                        while (nowMin % i === 0 && maxMin % i === 0) {
                            nowMin /= i;
                            maxMin /= i;
                        }
                    }
                }
                this.currentFraction = [nowMin, maxMin];
                break;
            }
        }
    }

    resize() {
        const w = window.innerWidth;
        const h = window.innerHeight - 150;
        let max = 0;
        if (w < h) {
            if (w*2 < h) {
                max = w;
            } else {
                max = h / 2;
            }
        } else {
            if (h*2 < w) {
                max = h;
            } else {
                max = w / 2;
            }
        }
        this.diameter = Math.round(.8 * max);
        this.textSize = this.diameter / 3;
    }

    refresh() {
        const observable = this.icalService.get()
        if (!observable) {
            this.dialog.open(ErrorComponent, {
                data: "Please enter a valid ICAL-Url in Settings"
            });
            return;
        }
        observable.subscribe(events => {
            console.log(events);
            this.events = events;
            this.setProgress();
            setTimeout(() => {
                setInterval(() => {
                    this.setProgress();
                }, 1000);
            }, Number(moment().format("X")) % 1000);
            this.resize();
            window.addEventListener("resize", () => {
                this.resize();
            });
        });
    }

    openSettings() {
        this.dialog.open(SettingsComponent);
    }

    ngOnInit(): void {
        this.storage.get$("ical-url").subscribe(() => {
            this.refresh();
        });
    }
}
