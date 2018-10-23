from flask import Flask
from flask_login import LoginManager
from src.client import bootstrap_system


app = Flask(__name__)
app.secret_key = 'very-secret-123'  # Used to add entropy
system = bootstrap_system()

# Login manager stuff
login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = 'login'


@login_manager.user_loader
def load_user(user_id):
    return system.get_user_by_id(user_id)


# Loads data
# warehouse, dm, user_db = OnlineShoppingData.load_data()
