# Cryptography in C

# Table of contents
1. [Summary](#summary)
2. [Content](#content)
3. [Installations](#installations)
4. [Documentation](#documentation)
    1. [Doxygen](#doxygen)
    2. [Technical sources](#sources)
5. [Metainformations](#meta)
    1. [Changelog](#changelog)
    2. [License](#license)
    3. [Authors](#authors)

## Project summary <a name="summary"></a>
Exploration of the topic of cryptography in C.
This project is intended to be as minimalist and straight forward as possible. 
The content is not ground breaking as it is meant to be for educational purposes. 
The project only uses Makefile, CMake and C.

## Content <a name="content"></a>
- Ciphers
    - aes
    - rsa (ToDo)
    - des
- Fingerprints (ToDo)
    - sha-1 
    - sha-224
    - sha-256
    - sha-384
    - sha-512
    - sha-512/224
    - sha-512/256
- Helpers
    - 64-bits bitset
    - galois field $2^8$

## Installations <a name="installations"></a>

## Documentation <a name="documentation"></a>
### Doxygen <a name="doxygen"></a>


### Technical sources <a name="sources"></a>
- FIPS-46-3, N.I.S.T.
- FIPS-192, N.I.S.T.
- FIPS-197-1, N.I.S.T.
- FIPS-180-4, N.I.S.T.
- FIPS-202, N.I.S.T.

## Metainformations <a name="meta"></a>
### Changelog <a name="changelog"></a>
- [23/08/2023] Moved github repo.
- [27/04/2023] A.E.S. version NIST.FIPS-197.
- [19/02/2024] D.E.S. version NIST.FIPS-46.

### License <a name="license"></a>
MIT License
Copyright (c) 2023 nm

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

### Authors <a name="authors"></a>
Nicolas Misbert