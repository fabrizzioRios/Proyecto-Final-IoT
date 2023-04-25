from django.shortcuts import render, redirect
from django.conf import settings
from django.core.mail import send_mail
from django.contrib.auth import login
from services.forms import SupplierForm, UserForm
from django.views import generic
from services.models import Supplier
import os
import subprocess
import time


# from services.mqtt_manager import run

# Create your views here.
class SupplierList(generic.ListView):
    model = Supplier
    context_object_name = "supplier_list"
    template_name = "supplier_list.html"


def profile(request):
    return render(request, 'profile.html')


def home(request):
    return render(request, 'home.html')


def menu(request):
    if request.method == "POST":
        username = str(request.user)
        topic = str(request.POST['asunto'])
        value = str(request.POST['mqtt'])
        ip = "10.2.0.15"
        print(topic, username, value)
        command = '/home/frios/Escritorio/DjangoProjects/Bao_fu_pweb2/services/client'
        os.chdir(command)
        run_command = subprocess.Popen(['make'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output, errors = run_command.communicate()
        print(f"Output {output.decode('utf-8')}")

        if value == '1':
            print(type(username))
            print(type(topic))
            print(type(value))
            executable_path = f'./client'
            subprocess.run([executable_path, str(len(username)), ip, value], capture_output=True,
                           text=True)
            time.sleep(3)
            context = {
                "value": value,
                "topic": f"Has publicado en {topic}"
            }
            return render(request, 'menu.html', context=context)
        if value == '2':
            print(type(username))
            print(type(topic))
            print(type(value))
            executable_path = f'./client'
            program_process = subprocess.run([executable_path, str(len(username)), ip, value], capture_output=True,
                                             text=True)
            print(f"Hi process completed {program_process.stdout}")

            time.sleep(3)
            context = {
                'value': value,
                'topic': f"Estas suscrito a {topic}"
            }
            return render(request, 'menu.html', context=context)
    else:
        return render(request, 'menu.html')


def about(request):
    return render(request, 'about.html')


def contact(request):
    return render(request, 'contact.html')


def supplier_register(request):
    form_supplier = SupplierForm()
    if request.method == 'POST':
        form_supplier = SupplierForm(request.POST)
        form_supplier.save()
        return render(request, 'supplier.html', {'form': form_supplier})
    if request.method == 'GET':
        return render(request, 'supplier.html', {'form': form_supplier})


def signup(request):
    local = "http://127.0.0.1/"
    if request.method == 'POST':
        form_user = UserForm(request.POST)
        if form_user.is_valid():
            user = form_user.save()
            user.refresh_from_db()
            user.save()
            login(request, user)
            subject = 'Bienvenido a la familia Bao Fu!\n'
            message = f'Hola {user.username} !, estamos contentos de tenerte con nosotros <a ' \
                      f'href="{local}">login<a>'
            email_from = settings.EMAIL_HOST_USER
            recipient_list = [user.email, ]
            send_mail(subject, message, email_from, recipient_list)
            return redirect('login')
    else:
        form_user = UserForm()
    return render(request, 'signup.html', {"form": form_user})
