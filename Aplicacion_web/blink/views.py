from django.core import serializers
from django.shortcuts import render
from django.http import HttpResponse
from .models import  Arduino
from .serializers import ArduinoSerializer
import requests

from django.http import JsonResponse


def modo(request,id):

    arduino_history = Arduino.objects.filter(id=id)
    arduino_control = Arduino.objects.get(id=id)


    data = {'arduino_control' : arduino_control,
            'arduino_history' : arduino_history,

    }
    return render(request, 'blink/modo.html', data)


def inicio(request):
    arduino_history = Arduino.objects.all().order_by('id')


    data = {
            'arduino_history': arduino_history,
            }

    return render(request, 'blink/home.html', data)


def lista(request):

    arduino = Arduino.objects.all().order_by('id')
    data = { 'arduino': arduino}

    return render(request,'blink/lista.html',data)



def read(request,id):

    arduino_control = Arduino.objects.filter(id=id).last()
    estado = arduino_control.estado
    nombre = arduino_control.nombre
    id = arduino_control.id

    return JsonResponse({'estado': estado , 'nombre': nombre , 'id':id,})


def update(request,id):

   arduino = Arduino.objects.get(id=id)
   estado = request.GET['set']
   arduino.estado = estado
   arduino.save()

   print("Respuesta")
   response = requests.get('http://arduino2.local/')
   print(response)

   return JsonResponse(estado, safe=False)




