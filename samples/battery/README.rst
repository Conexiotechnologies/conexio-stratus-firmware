.. _boards_nrf_battery:

On-board Battery Voltage Measurement
###########################

Overview
********

This sample demonstrates using Nordic configurations of the Zephyr ADC
infrastructure to measure the voltage of the device power supply.  Two
power supply configurations are supported:

* If the board devicetree has a ``/vbatt`` node with compatible
  ``voltage-divider`` then the voltage is measured using that divider.
* Otherwise the power source is assumed to be directly connected to the
  digital voltage signal, and the internal source for ``Vdd`` is
  selected.

An example of a Conexio Stratus devicetree node describing a voltage divider 
for battery monitoring:

.. code-block:: none

   / {
   	vbatt {
         compatible = "voltage-divider";
		   io-channels = <&adc 7>;
		   output-ohms = <100000>;
		   full-ohms = <(100000 + 100000)>;
		   power-gpios = <&gpio0 25 0>;
   	};
   };

Note that in many cases where there is no voltage divider the digital
voltage will be fed from a regulator that provides a fixed voltage
regardless of source voltage, rather than by the source directly.  In
configuration involving a regulator the measured voltage will be
constant.

The sample provides discharge curves that map from a measured voltage to
an estimate of remaining capacity.  The correct curve depends on the
battery source: a standard LiPo cell requires a curve that is different
from a standard alkaline battery.  Curves can be measured, or estimated
using the data sheet for the battery.

Application Details
===================

The application initializes battery measurement on startup, then loops
displaying the battery status every five seconds.

Requirements
************

A Nordic-based board, optionally with a voltage divider specified in its
devicetree configuration as noted above.

Building and Running
********************

   west build -b conexio_stratus_ns

Sample Output
=============

.. code-block:: console

   Conexio Stratus battery example
   [0:00:00.016]: 4078 mV; 10000 pptt
   [0:00:04.999]: 4078 mV; 10000 pptt
   [0:00:09.970]: 4078 mV; 10000 pptt
   [0:00:14.939]: 4069 mV; 10000 pptt
   [0:00:19.910]: 4078 mV; 10000 pptt
   [0:00:24.880]: 4069 mV; 10000 pptt
