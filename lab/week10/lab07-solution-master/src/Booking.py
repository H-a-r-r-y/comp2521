class Booking(object):

    def __init__(self, customer, period, car, location):
        self._customer = customer
        self._period = period
        self._car = car
        self._location = location

    @property
    def booking_fee(self):
        fee = self._car.get_fee(self._period)
        return fee

    @property
    def location(self):
        return self._location

    def __str__(self):
        return "Booking for: {}, {}".format(self._customer, self._car)
