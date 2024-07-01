from setuptools import find_packages
from setuptools import setup

setup(
    name='minibot_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('minibot_interfaces', 'minibot_interfaces.*')),
)
