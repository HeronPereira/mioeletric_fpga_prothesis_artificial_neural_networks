# mioeletric_fpga_prothesis_artificial_neural_networks
End project of Bachelor of Science course 2016. Created a hand prothesis using Artificial Neural Networks in a FPGA.

This project takes and input from a mioelectric sensor and converts muscle contraction into signal and is received to a Arduino board.
This Arduino board send this info to a FPGA device that has a 2 layer multilayer percetron artificial neural network (ANN), that returns to the Arduino board how much the hand should grip. To be able to generate this algorithm the library of fixed_pkg and fixed_float_type was used.
The Arduino board receives this data and controls a servo motor that contracts the hand grip.

A C code of the ANN was created first to trainning the model.

The training data was captured from the subject using the same sensor.
