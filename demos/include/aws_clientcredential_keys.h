/*
 * FreeRTOS V202012.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/*
 ****************************************************************************
 * NOTE!
 * This file is for ease of demonstration only.  Secret information should not
 * be pasted into the header file in production devices.  Do not paste
 * production secrets here!  Production devices should store secrets such as
 * private keys securely, such as within a secure element.  See our examples that
 * demonstrate how to use the PKCS #11 API for secure keys access.
 ****************************************************************************
 */

#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

/*
 * @brief PEM-encoded client certificate.
 *
 * @todo If you are running one of the FreeRTOS demo projects, set this
 * to the certificate that will be used for TLS client authentication.
 *
 * @note Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyCLIENT_CERTIFICATE_PEM                   "-----BEGIN CERTIFICATE-----\n"\
"MIICODCCAd6gAwIBAgIUfL+Iu0ApekYOMPXPwNlk+Bz7V0kwCgYIKoZIzj0EAwIw\n"\
"OjELMAkGA1UEBhMCS1IxFzAVBgNVBAoMDklDVEsgSG9sZGluZ3MuMRIwEAYDVQQD\n"\
"DAlqc3BsZWUgQ0EwHhcNMjEwMzA4MDEzODU2WhcNMjYwMzA3MDEzODU2WjBJMQsw\n"\
"CQYDVQQGEwJLUjEWMBQGA1UECgwNSUNUSyBIb2xkaW5nczERMA8GA1UECwwISVNG\n"\
"IERlbW8xDzANBgNVBAMMBmpzcGxlZTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IA\n"\
"BOzu5sCoEhiTAOy3xxdK7uyp4Z8MeTprbQMkT+VFRJbA0yYKxqPLsmtQU8bmmeFF\n"\
"/BMCx/FOZZhzqtANMp29S0KjgbIwga8wCQYDVR0TBAIwADAfBgNVHSMEGDAWgBTY\n"\
"gAZVslDcJ/RqKBrFuNm/fbOIvTAdBgNVHQ4EFgQUl0iw1m9qZgvFaWrlQ7xpYOyX\n"\
"I+MwCwYDVR0PBAQDAgXgMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjA2\n"\
"BgNVHREELzAtgg93d3cubGVzc3RpZi5jb22CC2xlc3N0aWYuY29tgg0qLmxlc3N0\n"\
"aWYuY29tMAoGCCqGSM49BAMCA0gAMEUCIQDU4KIMAgpjDAexr7fXckmmZJONTbfm\n"\
"9az+hboniYUDcAIgXeqhHZLj5iqvO8bzpHt7jyGBYasCoHEIeWboI8COgzU=\n"\
"-----END CERTIFICATE-----"

/*
 * @brief PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 *
 * @todo If you are using AWS IoT Just in Time Registration (JITR), set this to
 * the issuer (Certificate Authority) certificate of the client certificate above.
 *
 * @note This setting is required by JITR because the issuer is used by the AWS
 * IoT gateway for routing the device's initial request. (The device client
 * certificate must always be sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html,
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set below to NULL.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM    NULL

/*
 * @brief PEM-encoded client private key.
 *
 * @todo If you are running one of the FreeRTOS demo projects, set this
 * to the private key that will be used for TLS client authentication.
 * Please note pasting a key into the header file in this manner is for
 * convenience of demonstration only and should not be done in production.
 * Never past a production private key here!.  Production devices should
 * store keys securely, such as within a secure element.  Additionally,
 * we provide the corePKCS library that further enhances security by
 * enabling keys to be used without exposing them to software.
 *
 * @note Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */
#define keyCLIENT_PRIVATE_KEY_PEM                   "-----BEGIN EC PRIVATE KEY-----\n"\
"MHcCAQEEIJRUNHarRYl6PAycr+0snYl6pi2hbk/ES1+QIkeZizTsoAoGCCqGSM49\n"\
"AwEHoUQDQgAE7O7mwKgSGJMA7LfHF0ru7Knhnwx5OmttAyRP5UVElsDTJgrGo8uy\n"\
"a1BTxuaZ4UX8EwLH8U5lmHOq0A0ynb1LQg==\n"\
"-----END EC PRIVATE KEY-----"

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
