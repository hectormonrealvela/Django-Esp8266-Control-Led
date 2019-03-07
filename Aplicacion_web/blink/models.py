from django.db import models



class Arduino(models.Model):

    nombre = models.CharField(max_length=200 )
    estado = models.BooleanField()
    time = models.DateTimeField(auto_now=True, editable=True)
    url = models.CharField(max_length=200 , null = True, blank=True)

    def __str__(self):
        return str(self.nombre) + str(self.estado) + str(self.time) +str(self.url)
