from setuptools import setup

package_name = 'py_sub'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Omar Ziad',
    maintainer_email='omar.ziad1@outlook.com',
    description='Subscriber Node that calculates velocity and acceleration using position and time',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
                'listener = py_sub.subscriber:main',
        ],
},
)
