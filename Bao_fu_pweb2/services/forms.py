from django import forms
from services.models import User, Supplier


class UserForm(forms.ModelForm):
    class Meta:
        model = User
        fields = ['username', 'first_name', 'last_name', 'email', 'password', 'age', 'phone_number', 'address']
        widgets = {
            'password': forms.PasswordInput(),
        }


class SupplierForm(forms.ModelForm):
    class Meta:
        model = Supplier
        fields = ['name', 'manager_name', 'phone_number', 'description', 'address']
