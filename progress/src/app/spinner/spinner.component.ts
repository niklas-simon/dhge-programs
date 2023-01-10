import { Component, Input } from '@angular/core';

@Component({
    selector: 'app-spinner',
    templateUrl: './spinner.component.html',
    styleUrls: ['./spinner.component.scss']
})
export class SpinnerComponent {
    @Input() progress: number = 0;
    @Input() fraction: number[] = [0, 0];
    @Input() diameter: number = 0;
    @Input() caption: string = "";
    @Input() textSize: number = 0;
}
