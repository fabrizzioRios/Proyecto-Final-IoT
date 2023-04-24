# Proyecto-Final-IoT 💻

En este proyecto final, se busca la implementacion de un servidor o broker de MQTT programado en el lenguaje C, ajustado a una pagina web basada en la tecnologia de Django.

### Requerimientos 📋
- Python > 3.9.0 
- Django > 4.1.5

## Objetivo 🎯

Creacion de una pagina web basada en Django, HTML y CSS utilizando la tecnologia de MQTT Broker-Server creado en C para hacer suscripciones y publicaciones en el sitio de un restaurante de comida China.

## Build 🛠️
Antes que nada, debemos de asegurarnos de estar en un dispositivo con el sistema operativo linux. Es recomendado que la version de este sea Linux Ubuntu 22.04.

Aqui hay un tutorial de como descargar e instalar Ubuntu. https://www.youtube.com/watch?v=ESkuXK71Y74.

## Set up de Python 🐍
Para poder correr nuestra pagina web de manera local, debemos de comprobar la version de Python de nuestro sistema. Regularmente los sistemas operativos MACOS y Linux ya cuentan con una version de Python instalada, sin embargo, esta no cumple con las caracteristicas necesarias para utilizar el framework de Django

Vamos a comprobar que la version de Python sea la 3.9.0 o mayor a esta:

`python3`

En dado caso de que no este instalado, tendremos que instalar la version adecuada.

Aqui hay un tutorial de como descargar e instalar python 3 en Ubuntu. https://www.youtube.com/watch?v=w7v4CZt1po8
 
## Set up del entorno y descarga de librerias (OPCIONAL) 🗂️

Vamos a instalar una libreria para control de entornos virtuales llamada virtualenvwrapper, de esta forma podremos encapsular nuestro entorno virtual y manejarlo de manera mas facil.

Aqui hay un tutorial para descargar virtualenvwrapper en Ubuntu. https://virtualenvwrapper.readthedocs.io/en/latest/install.html

Despues de descargar la libreria, procederemos a crear nuestro entorno y descargar las librerias.

Utilizaremos los siguientes comandos:

`mkvirtualenv baofu_project`

`workon baufu_project`

`pip3 install django==4.1`

## Clonar repositorio 📂

Antes de clonar el repositorio, deberemos de tener nuestro entorno ya creado y django ya descargado en nuestro entorno.

En dado caso de que no estes usando entornos virtuales, solo deberas de tener Django instalado.

`pip3 install django==4.1`

Procederemos a crear un directorio donde tendremos nuestros proyectos de Django.

`mkdir DjangoProjects`
`cd DjangoProjects`

Antes de crear el proyecto, debemos asegurarnos de tener el entorno virtual activado. Si ya esta activado, debera aparecer su nombre al lado izquiero del path de la terminal. Si no, deberar activarlo con el siguiente comando (SOLO SI ESTAS USANDO ENTORNOS VIRTUALES)

`workon baofu_project`

De igual forma si tienes tu entorno activado o si no estas usando entornos, procederemos a clonar el repositorio y activar el servidor de Django.

`git clone https://github.com/fabrizzioRios/Proyecto-Final-IoT.git`

Ya tendremos el repositorio clonado, solo quedara activar el server.

## Activacion del Server de Django 🔫🤠

Despues de clonar el server deberemos de usar los comandos de django para activar el server.

Solamente tendremos que pasar este comando al prompt y quedara corriendo en local el servidor.

`python manage.py runserver`

Y listo, debera aparecer una direccion local y podras acceder desde el localhost a la pagina web.

# Autores ✒️
- Jose Sebastian Chavez Navarro 
- Luis Fabrizzio Rios Ruiz 
