import { DialogRef } from '@angular/cdk/dialog';
import { Component, OnInit } from '@angular/core';
import { StorageService } from '../storage.service';

@Component({
    selector: 'app-settings',
    templateUrl: './settings.component.html',
    styleUrls: ['./settings.component.scss']
})
export class SettingsComponent implements OnInit {
    url = "";

    constructor(private storage: StorageService, private dlgRef: DialogRef) {}

    close() {
        this.dlgRef.close();
    }

    save() {
        this.storage.set("ical-url", this.url);
        this.close();
    }

    ngOnInit(): void {
        this.url = this.storage.get("ical-url");
    }
}
