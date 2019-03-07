from .models import Arduino
from rest_framework import serializers


class ArduinoSerializer(serializers.ModelSerializer):
    class Meta:
        model = Arduino
        fields = '__all__'




