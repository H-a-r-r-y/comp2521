from abc import ABC


class Car(ABC):

    def __init__(self, name, model, rate, rego):
        self._name = name
        self._model = model
        self._daily_rate = rate
        self._rego = rego
        self._bookings = []

    def get_name(self):
        return self._name

    def get_model(self):
        return self._model

    def get_fee(self, period):
        return period * self._daily_rate

    def get_rego(self):
        return self._rego

    def __str__(self):
        return "Car details: {0},{1}".format(self._name, self._model)

    def get_bookings(self):
        return self._bookings

    def add_booking(self, booking):
        self._bookings.append(booking)


class SmallCar(Car):

    def __init__(self, name, model, rego):
        super().__init__(name, model, 50, rego)

    def __str__(self):
        return "Small Car details: {0},{1}".format(self._name, self._model)

class MediumCar(Car):
    def __init__(self, name, model, rego):
        super().__init__(name, model, 75, rego)

    def __str__(self):
        return "Medium car details: {0},{1}".format(self._name, self._model)

class LargeCar(Car):
    def __init__(self, name, model, rego):
        super().__init__(name, model, 100, rego)

    def get_fee(self, period):
        fee = super().get_fee(period)
        if period >= 7:
            fee = fee * 0.95
        return fee

    def __str__(self):
        return "Large car details: {0},{1}".format(self._name, self._model)

class PremiumCar(Car):

    def __init__(self, name, model, rego):
        super().__init__(name, model, 150, rego)
        self._premium_tariff = 0.15

    def get_fee(self, period):
        return super().get_fee(period) * 1.15

    def __str__(self):
        return "Premium car details: {0},{1}".format(self._name, self._model)
