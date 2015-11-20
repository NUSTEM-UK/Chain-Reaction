# Chain Reaction Workshop

[Think Physics](http://thinkphysics.org) is an outreach initiative based at Northumbria University in North-East England. We support children and their schools, teachers, parents and carers in STEM choices, from pre-school to post-16.

One strand of our work is, loosely, 'maker' activities. In November 2015 we started experimenting with a 'chain reaction'-type workshop (if we mention *Rube Goldberg*, we should also note *Heath Robinson*, since we're in the UK). The workshop:

* Is open-ended
* Is overtly creative
* Blends physical and digital domains
* Is cooperative: participants work in small teams and assemble towards an outcome shared by the whole group
* Assumes little, or no, programming experience.

## This code

This code is intended to turn a sensor+Arduino+servo combination into a chain reaction building block alongside cardboard, chopsticks, plastic dinosaurs and all the rest. By changing the initial lines of the code, the participant can:

* Patch in one of several sensor types
* Patch in one of a few output variants
* Determine system behaviour

The pinouts are set so, in principle, all the different inputs and outputs can be simultaneously connected to one Arduino Uno. At present, the code only handles one input/output pairing - a subject for future work.

### Inputs

As of November 2015, the code handles as input:

* Simple Arduino pinout switch; set as `INPUT_PULLUP` then flipped, so short the pin to ground.
* Light-dependent resistor
* Force-sensitive resistor
* Flex sensor
* IR Distance sensor
* Potentiometer
* Tilt switch
* Hall Effect magnetic field switch
* Load sensor (50kg strain gauge)

TODO: Document component choices for these, where relevant.

### Outputs

As of November 2015, the code handles as output:

* Standard servo
* Continuous-rotation servo
* Simple switched pin output, for driving eg. LEDs
* Relay, via a relay shield

TODO: Document component choices, where relevant  
TODO: Break relay behaviour out into a separate codebase, the shield needs to be handled differently.
