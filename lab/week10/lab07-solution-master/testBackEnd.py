import pytest
from flask import Flask
from flask_login import LoginManager
from datetime import datetime
from flask import render_template, request, redirect, url_for, abort
from flask_login import current_user, login_required, login_user, logout_user
from src.Location import Location
from src.Car import Car, PremiumCar
from src.CarRentalSystem import CarRentalSystem
from src.Customer import Customer



system = CarRentalSystem()


def test_1():


	user_name = "Matt"
	password = "pass"
	system.new_customer(Customer(user_name, password, 1531))
	user = system.validate_login(user_name, password)
	assert user != None

	car_name = "Tesla"
	car_model = "model x"
	rego = 0
	system.add_car(PremiumCar(car_name, car_model, str(rego)))
	car = system.get_car(str(rego))
	assert car.get_name() == car_name
	assert car.get_model() == car_model


	location = Location("Sydney", "Mel")
	assert location

	date_format = "%Y-%m-%d"
	start_time = datetime.strptime("2018-11-11", date_format)
	end_time = datetime.strptime("2018-12-12", date_format)

	diff = end_time - start_time

	booking = system.make_booking(current_user, diff, car, location)
	assert booking._period == diff
	assert booking._car == car
	assert booking.location == location
	assert car.get_bookings()[0]
	assert system._bookings[0]

def test_2():
	user_name = "Issav"
	password = "pass"
	system.new_customer(Customer(user_name, password, 1531))
	user = system.validate_login(user_name, password)
	assert user != None

	car_name = "Tesla"
	car_model = "model x"
	rego = 0
	system.add_car(PremiumCar(car_name, car_model, str(rego)))
	car = system.get_car(str(rego))
	assert car.get_name() == car_name
	assert car.get_model() == car_model


	location = Location("Sydney", "Mel")
	assert location

	date_format = "%Y-%m-%d"
	start_time = datetime.strptime("2018-11-11", date_format)
	end_time = datetime.strptime("2018-11-10", date_format)

	diff = end_time - start_time

	booking = system.make_booking(current_user, diff, car, location)
	system = CarRentalSystem()


def test_1():


	user_name = "Matt"
	password = "pass"
	system.new_customer(Customer(user_name, password, 1531))
	user = system.validate_login(user_name, password)
	assert user != None

	car_name = "Tesla"
	car_model = "model x"
	rego = 0
	system.add_car(PremiumCar(car_name, car_model, str(rego)))
	car = system.get_car(str(rego))
	assert car.get_name() == car_name
	assert car.get_model() == car_model


	location = Location("Sydney", "Mel")
	assert location

	date_format = "%Y-%m-%d"
	start_time = datetime.strptime("2018-11-11", date_format)
	end_time = datetime.strptime("2018-12-12", date_format)

	diff = end_time - start_time

	booking = system.make_booking(current_user, diff, car, location)
	assert booking._period == diff
	assert booking._car == car
	assert booking.location == location
	assert car.get_bookings()[0]
	assert system._bookings[0]

def test_2():
    with pytest.raises(Exception) as err:
        user_name = "Issav"
        password = "pass"
        system.new_customer(Customer(user_name, password, 1531))
        user = system.validate_login(user_name, password)
        assert user != None

       	car_name = "Tesla"
        car_model = "model x"
        rego = 0
        system.add_car(PremiumCar(car_name, car_model, str(rego)))
        car = system.get_car(str(rego))
        assert car.get_name() == car_name
        assert car.get_model() == car_model


        location = Location("Sydney", "Mel")
        assert location

        date_format = "%Y-%m-%d"
        start_time = datetime.strptime("2018-11-11", date_format)
        end_time = datetime.strptime("2018-11-10", date_format)

        diff = end_time - start_time

        booking = system.make_booking(current_user, diff, car, location)
        assert err.errors['period'] == 'The period is not valid'
 

def test_3():
    with pytest.raises(Exception) as err:
        user_name = "Taylor"
        password = "pass"
        system.new_customer(Customer(user_name, password, 1531))
        user = system.validate_login(user_name, password)
        assert user != None

       	car_name = "Tesla"
        car_model = "model x"
        rego = 0
        system.add_car(PremiumCar(car_name, car_model, str(rego)))
        car = system.get_car(str(rego))
        assert car.get_name() == car_name
        assert car.get_model() == car_model


        location = Location("Sydney", "Mel")
        assert location

        date_format = "%Y-%m-%d"
        start_time = datetime.strptime("", date_format)
        end_time = datetime.strptime("2018-11-10", date_format)

        diff = end_time - start_time

        booking = system.make_booking(current_user, diff, car, location)
        assert err.errors['start_date'] == 'The date is not valid'
