#include <pgmspace.h>

#define SECRET
#define THINGNAME "ESP32_Test"  //change this

const char WIFI_NAME[] = "tipu";                                                         //change this
const char WIFI_PASS[] = "tipu1234@";                                                   //change this
const char AWS_IOT_ENDPOINT[] = "a1aqkedukfaxny-ats.iot.ap-southeast-1.amazonaws.com";  //change this

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(

-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----

)EOF";

// Device Certificate  (CRT)
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(

-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAMIPy4tYkMO6R+TA5R9Aog8nu3dVMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDA4MjcxNzM4
NTZaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQD3MRilpOl+JKGXxkZ5
lFfXCA2LQMOIGo8+zqfQdrsIvK7Rkpvv2BgJ126KGLap/pOgX1tvK6kO6uKTRqpM
ntIXp/FizxQnrrasAa3vlIvkLCaZAt3wxdICXFf8TEExPR8RF9Qs6Zk3zlhU2Gg/
TKnaI9YnyBUuauKjtwP9C8iucpVaRuSh6kYIU0exR6ShQfOfQJ10pqbZAwcEdG3+
/MQ+nbpU10yUWYgqv2JbinMYt7PommdiIUVnMgjMjAgVmBB0XRzS6V32Yw/9W59z
eckP2cZR+V8QzCMlPgsLjllJ+0Zl3crP3xe6BviOpkTSkwUD0kvd5XfWwSHfQ9Uw
ddZ9AgMBAAGjYDBeMB8GA1UdIwQYMBaAFLcVfgU3lU9zi5JdEkrlIpA2iV87MB0G
A1UdDgQWBBRAGz31ulunWLiO5rPBmBgOlLW9hjAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAhu8/7c8NCdeKLK92YQsljAFk
Xe3XqrbBiqzillV9pU4bWWvnsftsk8b2fAxJFcIrzdgVFMrnGGvQKRocFTWpgHRD
7hPG4iB2k3ifLWQNgPXlje9dfGx9uOY/Lzk/MrTu2bsfpINlo4dXWQoh7+8QWQDZ
p/MTMho0diro3n/8CO9x95dTx0Cz57XbWMVpA2taQodksqWu/kuBiy7T2hgVDyFu
09q7TwsEwlnZzYnXwrR/Ir5B0KvQfoiwhscp/xp8HpFAYB2mPwXj68W2OVvNvtyv
eU7tXjn1ckRl2i2wYoXkP5cmX82BingP4sod6yhcVayuPzvNKLVFjbZiHGcUsw==
-----END CERTIFICATE-----



)KEY";

// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
  
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEA9zEYpaTpfiShl8ZGeZRX1wgNi0DDiBqPPs6n0Ha7CLyu0ZKb
79gYCdduihi2qf6ToF9bbyupDurik0aqTJ7SF6fxYs8UJ662rAGt75SL5CwmmQLd
8MXSAlxX/ExBMT0fERfULOmZN85YVNhoP0yp2iPWJ8gVLmrio7cD/QvIrnKVWkbk
oepGCFNHsUekoUHzn0CddKam2QMHBHRt/vzEPp26VNdMlFmIKr9iW4pzGLez6Jpn
YiFFZzIIzIwIFZgQdF0c0uld9mMP/Vufc3nJD9nGUflfEMwjJT4LC45ZSftGZd3K
z98Xugb4jqZE0pMFA9JL3eV31sEh30PVMHXWfQIDAQABAoIBAQCxP2ot9Idc5UVd
wFXufflSfjq//Gt4n5rRbXuVll1c0XcFXXwlSi1KeUiRC1GHqb0PhPDaUVNDGBfp
hQU+Na/uOIV01YndPoFL61Rec4Sv0xzGIPEl4aNKAA8zITap6Orq5cxFfCdahcJ+
7EIsCXvNqF66XdUaWJg0zlm0zAtVUfmUxH0U7Toq09hljGmtFNdjOMZGIDdsHCfA
yQsx/gJmVnFAJfnLc8haEwpYrek4RKE1pU9I13I/URPtzuFzIXeJPKNAp71dXPsS
VrE69g7lsp5ak6oeRM3EmB83UNJ+laa3D2Ta4mdlFZrO0AeyUz6Z4i9e8pbj1j73
CPOKM8iBAoGBAPxTyJgvS+UI4xwqh4Tj0KJzTMw8Moy4t/Xf+NvcCG6KJ7W1nTyw
FvbMAcSMPGirFN/PZBVBPYAVQFUzjESsBlT1gFPEfMYYB0JvYuHreF9WHssmHBqc
deP8KN5OcIIDsw9SGglI03tB2PB6WYIeXPR3i+r13RO2CNEAaKPOpT7hAoGBAPrK
LUsYLlkb/pjJgbQ07YwofgawgANU3tnKISxTZiTyY/HxvwGP47ybzm5TDHZ8fLFM
LsgcuUjIiXy8PD3MbXxakyyqGzdx9cF5t/s9BHhJz8pvlWYLeeEgf3QSq9WLoSa/
LzBeZNCAoQrT/HLwHnXjqrNVZj/B1opWAGcHh5cdAoGBAOCfITJA4FoaaDq5rXxi
ZWdIJvSlHgbhpXnvERV/sc3dlO4Qp9HPnBHFmElE4b33lpSKhbjaJApyYJu4UMUN
MnHNPpjTkJOz7jp499jQCo8sFiuYWGpkIBp9blBAGa3T50HbP6xGNWVDQAELmcTY
jL1f8qGOj2itovmTWJOCMN5hAoGAJIOnUJW2udavnQNJ1TkXlR6YKtUr7lA/Giqp
5dBGwP5huupdyxZuLBnrVnjVCbNaXF4hOZWlDInWKsklZEINdtuhLhGeYNZA1+im
9veNXQ4yKOFSOUdWeYbHx9ioGDF6Ry/y6PH1b74qtG7lBL8dUEDTq8S1XHcWi5G2
AUpBXakCgYEA7nOEcCiNH2ulrGe5vXfJMnsWuN1SyuvSs28iiEnZo9fDPOfROM5P
5wSggYNvm6amSOaSzKlIEnXS+JNrQpglaTJ1cE9xuqYTIwSDFgNTMLa8BJgM4fe7
tbQXqEjphn58lkmIbpIgm5d5OV1eJPmPta8lQHdy3tCoqKM4XnXyEzQ=
-----END RSA PRIVATE KEY-----


)KEY";
