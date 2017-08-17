## SpeX - NMR Spectrum simulation and plotting

### Introduction

This is a very old project of mine. It's the extension of a quantum mechanical NMR simulation and fitting program I wrote for my diploma thesis in theoretical chemistry. This software was based on the (in)famous LAOCOON program, written 1966 in FORTRAN IV. This means that LAOCOOn is exactly as old as I am. I only had the printed source code in a book by Bothner-By and Castellano.

To allow for dynamically allocated quantum state matrices (nuclear states have a finite number of states opposed to electron states …) I ported the old FORTRAN IV program to C++ using a modified library for complex number math written by Prof. Guido Buzzi-Ferraris.

### Current state

I don't expect this code to run anywhere without major adjustments. So stay tuned for updates :)