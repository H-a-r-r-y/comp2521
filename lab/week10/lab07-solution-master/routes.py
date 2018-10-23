from flask import render_template, request, redirect, url_for, abort
try:
    from flask_login import current_user, login_required, login_user, logout_user
except ImportError:
    from extra_for_windows.flask_login import current_user, login_required, login_user, logout_user
from server import app, system
from datetime import datetime
from src.Location import Location


@app.route('/')
def home():
    return render_template('home.html')


@app.route('/login', methods=['GET', 'POST'])
def login():
    """
    Task 1: complete this function
    """
    if request.method == 'POST':
        # Checks the user before logging in
        user = system.validate_login(request.form['username'], request.form['password'])
        if user is None:
            return render_template('login.html')
        login_user(user)
        # Next helps with redirecting the user to their previous page
        redir = request.args.get('next')
        return redirect(redir or url_for('home'))
    return render_template('login.html')


@app.route('/logout')
@login_required
def logout():
    logout_user()
    return redirect(url_for('home'))


@app.route('/404')
@app.errorhandler(404)
def page_not_found(e=None):
    return render_template('404.html'), 404


@app.route('/cars')
@login_required
def cars():
    """
    Task 2: At the moment this endpoint does not do anything if a search
    is sent. It should filter the cars depending on the search criteria
    """
    #  cars = system.cars
    make = request.args.get('make')
    model = request.args.get('model')
    if make == '':
        make = None
    if model == '':
        model = None
    cars = system.car_search(make, model)
    return render_template('cars.html', cars=cars)


@app.route('/cars/<rego>')
@login_required
def car(rego):
    car = system.get_car(rego)
    if car is None:
        abort(404)
    return render_template('car_details.html', car=car)


@app.route('/cars/<rego>/book', methods=["GET", "POST"])
@login_required
def book(rego):
    car = system.get_car(rego)
    
    if car is None:
        abort(404)
    if request.method == 'POST':
        try:
            errors = checkInputs(request.form['start_location'], 
                                                request.form['end_location'],
                                                request.form['start_date'],
                                                request.form['end_date'])
            if errors:
                raise BookingException(errors)
            else:
                date_format = "%Y-%m-%d"
                start_date = datetime.strptime(request.form['start_date'], date_format)
                end_date = datetime.strptime(request.form['end_date'], date_format)
                diff = end_date - start_date
                if 'check' in request.form:
                    fee = car.get_fee(diff.days)
                    return render_template(
                        'booking_form.html',
                        confirmation=True,
                        form=request.form,
                        car=car,
                        fee=fee,
                        errors={}
                    )
                elif 'confirm' in request.form:
                    location = Location(request.form['start_location'], request.form['end_location'])
                    booking = system.make_booking(current_user, diff.days, car, location)

                    return render_template('booking_confirm.html', booking=booking, errors={})
        except BookingException as a:
            return render_template(
                    'booking_form.html',
                    form=request.form,
                    car=car,
                    errors=a.errors
            )
    return render_template('booking_form.html', car=car, errors={})

@app.route('/cars/<rego>/bookings')
@login_required
def car_bookings(rego):
    """
    Task 3: This should render a new template that shows a list of all
    the bookings associated with the car represented by 'rego'
    """
    #  pass
    car = system.get_car(rego)
    return render_template('bookings.html', bookings=car.get_bookings())



def checkInputs(start_location, end_location, start_date, end_date):

    errors = {}
    if start_location == "":
        errors['start_location'] = "The location is not valid"
        
    if end_location == "":
        errors['end_location'] = "The location is not valid"
        
    date_format = "%Y-%m-%d"
    try:        
        start_date = datetime.strptime(start_date, date_format)
    except:
        errors['start_date'] = 'The date is not valid'
    try:
        end_date = datetime.strptime(end_date, date_format)
    except:
        errors['end_date'] = 'The date is not valid'
    
    if 'start_date' not in errors and 'end_date' not in errors:
        if start_date > end_date:
            errors['period'] = 'The period is not valid'
    return errors

class BookingException(Exception):
        
    def __init__(self, errors, msg=None):
        if msg is None:
            msg = "An error occured when booking."
        super(BookingException, self).__init__(msg)
        self.errors = errors
