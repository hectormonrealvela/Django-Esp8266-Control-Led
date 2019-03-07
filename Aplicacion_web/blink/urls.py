from django.urls import path
from django.conf.urls import url
from .views import inicio, lista, modo,read,update



urlpatterns = [
    path('', inicio, name='inicio'),
    url(r'^(?P<id>\d+)/read/',read, name="read"),
    url(r'^(?P<id>\d+)/update/',update, name="update"),
    path('lista/', lista, name ="lista"),
    url(r'^(?P<id>\d+)/$', modo, name='modo')



    ]


