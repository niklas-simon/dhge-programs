import { TestBed } from '@angular/core/testing';

import { IcalService } from './ical.service';

describe('IcalService', () => {
  let service: IcalService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(IcalService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
