import { Injectable } from '@angular/core';
import { ReplaySubject, Subject } from 'rxjs';

export interface Subscriber {
    key: string,
    subject: Subject<string>
}

@Injectable({
    providedIn: 'root'
})
export class StorageService {
    subscribers: Subscriber[] = [];
    constructor() { }

    set(key: string, value: string) {
        window.localStorage.setItem(key, value);
        for (const subscriber of this.subscribers) {
            if (subscriber.key === key) {
                subscriber.subject.next(value);
            }
        }
    }

    get(key: string, defval = "") {
        return window.localStorage.getItem(key) || defval;
    }

    get$(key: string) {
        const subject = new ReplaySubject<string>();
        subject.next(this.get(key));
        this.subscribers.push({
            key, subject
        });
        return subject;
    }
}
