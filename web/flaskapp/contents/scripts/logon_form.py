from flask.ext.wtf import Form
from wtforms.fields import TextField, PasswordField
from wtforms.validators import Required, Email
from wtforms.validators import Length

class PasswordForm(Form):
    password = PasswordField('Password', validators=[
        Required(u''),
        Length(min=4, message=(u'...definitely too short'))])
