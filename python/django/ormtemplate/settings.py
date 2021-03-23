# MYSQL SQL
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql',
        'NAME': 'lucadb',
        'USER': 'luca',
        'PASSWORD': 'calvito',
        'HOST': '127.0.0.1',
        'PORT': '3306',
    }
}

INSTALLED_APPS = (
    'standalone',
)

SECRET_KEY = 'SECRET KEY for this Django Project'
