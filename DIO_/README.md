# DIO Momentum Session

**Welcome** 👋

The **DIO (Direct I/O)** embedded session typically refers to an introductory session or class aimed at understanding **Direct Input/Output (DIO)** systems, often in the context of embedded systems programming. It generally involves learning how to interface with and control hardware through I/O operations at a low level.

---

## About the instructor

👋 Hi! I'm **Ahmed Mwafy**

* 🎓Mechatronics Level 200
* ✨Vice Technical Director at momentum
* 🤖 Embedded Systems
* 🧠 Autonomous systems

### Session Agenda:

* **What is AVR ..... ?**
* **DIO revision .**
* **The software architecture we're using .**
* **Writing DIO driver together**

---

### ATMEGA32 Overview

   ![Image](https://github.com/user-attachments/assets/70d8850c-d1a3-48e9-a15d-95939f62d15b)

The **ATmega32** is a microcontroller from Atmel (now part of Microchip Technology) that is part of the ATmega family. It is based on the  **AVR architecture** , which is known for its simplicity, performance, and low power consumption.

Key features of the ATmega32 include:

* **8-bit AVR microcontroller** : The ATmega32 is an 8-bit microcontroller, meaning it can process 8 bits of data at a time.
* **High-speed performance** : It operates at clock speeds up to  **16 MHz** .
* **Memory** :
* **32 KB of Flash memory** for storing programs.
* **2 KB of SRAM** for data storage during operation.
* **1 KB of EEPROM** for non-volatile storage (retained even when power is off).
* **I/O Pins** : It has 32 I/O pins that can be configured as input or output, allowing it to interact with external devices.
* **Timers** : It includes several timers and counters, which can be used for generating precise time delays, pulse width modulation (PWM), etc.
* **Analog-to-Digital Converter (ADC)** : 8-channel, 10-bit ADC, which allows the microcontroller to read analog signals (like from sensors) and convert them into digital data.
* **Communication** : It supports several communication protocols, including:
* **USART (Universal Synchronous and Asynchronous serial Receiver and Transmitter)** for serial communication.
* **SPI (Serial Peripheral Interface)** for high-speed communication with peripheral devices.
* **I2C (Inter-Integrated Circuit)** for communication with sensors or other devices.

The ATmega32 is widely used in embedded systems, DIY electronics, and educational projects due to its flexibility, ease of use, and extensive documentation available. It can be programmed using languages like C, and many development tools, such as Atmel Studio and the Arduino IDE (with additional support), can be used for programming the ATmega32.

---

# DIO Revision

The **DIO (Digital Input/Output)** peripheral in the **ATmega** microcontroller series is responsible for handling digital signals, allowing the microcontroller to read or write high or low voltage levels (0V or Vcc) on its I/O pins. This is crucial for various tasks like controlling LEDs, reading switches, or handling signals from sensors.

### **Digital I/O in ATmega Microcontrollers**

The ATmega series microcontrollers (like ATmega32, ATmega328, ATmega2560, etc.) provide a rich set of  **digital I/O pins** . These pins are highly configurable to either read digital input (high or low) or provide digital output (high or low).

#### **Key Features of DIO in ATmega:**

**Pin Direction Control** :

* Each I/O pin can be configured as either an **input** or  **output** .
* To configure a pin as input, you set the corresponding **Data Direction Register (DDR)** bit to `0`.
* To configure a pin as output, you set the corresponding **DDR** bit to `1`.

**Reading and Writing Data** :

* For  **output** , the value to be written (HIGH or LOW) is set in the **PORT** register.
* For  **input** , the value of the pin can be read from the **PIN** register.

**Pull-up Resistors** :

* If a pin is configured as an input, you can enable an **internal pull-up resistor** for that pin. This keeps the pin at a known state (HIGH) when no external connection is made.
* This is done by setting the corresponding bit in the **PORT** register when the pin is configured as an input.

**Interrupts** :

* The ATmega series allows for pin-change interrupts. This means that the microcontroller can trigger an interrupt when the state of a pin (configured as input) changes, which is useful for event-driven applications (e.g., detecting button presses).

### **Registers Involved in DIO Configuration:**
![Image](https://github.com/user-attachments/assets/65d2a248-4327-4fbc-9fb6-3efab63932ec)

**Data Direction Register (DDR)** :

* The **DDR** register controls the direction of each pin (input or output).
* Example: `DDRx` where `x` represents the port (e.g., DDRB for Port B, DDRC for Port C, etc.).
* If you set the bit to `1`, the corresponding pin is configured as  **output** ; if set to `0`, the pin is an  **input** .

    **Example** : Setting Pin 2 on Port B as an output:

 **PORT Register** :

* The **PORT** register is used to write data to the pins when they are configured as outputs. For inputs, it can be used to enable internal pull-up resistors.
* Example: `PORTx` where `x` represents the port (e.g., PORTB for Port B).


* <pre class="!overflow-visible" data-start="2729" data-end="2839"><div class="contain-inline-size rounded-md border-[0.5px] border-token-border-medium relative bg-token-sidebar-surface-primary dark:bg-gray-950"><div class="overflow-y-auto p-4" dir="ltr"><code class="!whitespace-pre language-c"><span>PB2
  </span></code></div></div></pre>
* **PIN Register** :
* The **PIN** register is used to **read** the state of an input pin.
* Example: `PINx` where `x` represents the port (e.g., PINB for Port B).

<pre class="!overflow-visible" data-start="2225" data-end="2282"><div class="contain-inline-size rounded-md border-[0.5px] border-token-border-medium relative bg-token-sidebar-surface-primary dark:bg-gray-950"></div></pre>

---

# **`Software Architecture Overview`**
![Image](https://github.com/user-attachments/assets/591ada46-4e85-451b-aa02-97f4593e80b1)
 
The software architecture, particularly in embedded systems and automotive software development, can be broken down into several layers for abstraction, modularity, and maintainability. One common approach is to use a layered structure involving  **MCAL** ,  **HAL** ,  **APP** , and **Library** components. Let’s break down what each of these terms means:

### 1.  **MCAL (Microcontroller Abstraction Layer)** :

The MCAL is a low-level layer that provides an abstraction between the microcontroller hardware and higher layers of the software. Its role is to handle direct interactions with the microcontroller's peripherals (such as GPIO, UART, ADC, PWM, etc.) and offer standard interfaces to the rest of the software.

* **Purpose** : To hide hardware-specific details and provide a standardized interface to the upper layers.
* **Key Features** :
* Manages direct hardware access (e.g., registers and bit-level manipulations).
* Provides drivers for hardware peripherals.
* Often hardware-specific and platform-dependent.

For example, in automotive systems, the MCAL can manage a microcontroller's timing, input/output, and communication modules, ensuring portability across different microcontroller platforms.

### 2.  **HAL (Hardware Abstraction Layer)** :

The HAL sits between the MCAL and the application layer (APP). It abstracts the hardware details further and provides a higher-level interface for hardware management. The HAL is designed to be independent of specific hardware implementations, making it easier to switch hardware platforms without significantly changing the upper layers of the software.

* **Purpose** : To provide a more hardware-agnostic interface than the MCAL.
* **Key Features** :
* Provides a higher-level interface to hardware components like UART, timers, and GPIO, compared to MCAL.
* Enables the reuse of code across different hardware platforms.
* Works with different microcontrollers or modules with minimal changes to the upper layers.

For instance, while the MCAL directly interacts with microcontroller registers to control a UART module, the HAL would expose functions like `HAL_UART_Transmit()` and `HAL_UART_Receive()`, which can be used without worrying about the underlying hardware implementation.

### 3.  **APP (Application Layer)** :

The APP layer is where the actual application logic resides. This layer communicates with the HAL to control the system's hardware without directly handling the low-level details. It defines the behavior of the system or device according to the project requirements.

* **Purpose** : To implement the business logic or application functionality, using the interfaces provided by the HAL and libraries.
* **Key Features** :
* Contains the core functionality of the system.
* Interacts with the HAL to control the hardware indirectly.
* Is typically platform-independent, focusing on the use case rather than hardware specifics.

For example, in an embedded system for a car, the APP layer might contain logic for controlling the dashboard display, reading sensor data, and managing vehicle status, all through interfaces provided by the HAL.

### 4.  **Library** :

Libraries in this context typically refer to collections of pre-written code that can be reused by the other layers. These can include general-purpose software modules, algorithms, or even specific functions that are needed by the MCAL, HAL, or APP layers.

* **Purpose** : To provide reusable code that can simplify development and offer standard functionalities.
* **Key Features** :
* Can include drivers, algorithms, communication protocols, or utility functions.
* Often reusable across various projects and layers.
* Optimized for specific tasks (e.g., communication protocols like CAN, SPI, or more complex signal processing).

For example, libraries for communication protocols (e.g.,  **CAN library** ) can be used by the HAL or APP to enable inter-device communication. Libraries can also contain algorithms for filtering sensor data or performing calculations for the application.

---

### Summary of How These Layers Interact:

* **MCAL** interacts directly with the microcontroller hardware.
* **HAL** provides a hardware-abstracted interface for the upper layers, including standardized access to hardware peripherals.
* **APP** contains the main application logic, using HAL and libraries to implement functionality.
* **Library** offers reusable code that can be employed by the other layers for tasks like communication, algorithms, or even hardware drivers.

This layered approach separates concerns and increases modularity, portability, and maintainability in embedded software development. It also facilitates easier testing and debugging since each layer is more isolated and can be developed independently.

---



The **MCAL (Microcontroller Abstraction Layer)** in AUTOSAR typically includes several files to manage different aspects of microcontroller hardware abstraction. These files help to separate the configuration, implementation, and interface details, providing a structured approach to handle low-level microcontroller operations. When it comes to organizing MCAL files, you may encounter the following types of files, which are part of the MCAL structure:

### 1. **reg**.h

* **Purpose** : This file contains the **register definitions** and **register mappings** for the microcontroller. It defines the hardware registers and their bit positions for controlling the various peripherals (like UART, ADC, GPIO, etc.).
* **Content** :
* Definitions of the registers as macros or constants.
* Hardware-specific configurations (often autogenerated based on the microcontroller's datasheet).
* **Example** : If you're working with a microcontroller, this file might define `#define UART_CTRL_REG 0x4000` for controlling the UART peripheral.

### 2. **prv**.h

* **Purpose** : This file contains **private functions** and low-level routines that are not meant to be directly accessed by other modules. It handles operations that are specific to the implementation of MCAL functions.
* **Content** :
* Private helper functions that manipulate registers or peripherals.
* Typically, functions defined here are not part of the public interface and are used only within the MCAL's implementation.
* It may also include lower-level interrupt service routines (ISRs) and other system-specific code.
* **Example** : Private functions like `static void enable_interrupts(void)` or `static void delay_ms(uint16_t time)` could be in this file.

### 3. **cfg**.h

* **Purpose** : The **configuration file** stores settings that can be tuned at compile time to adjust the behavior of MCAL components. These configurations might include timer settings, baud rates for UART, or other peripheral-specific options.
* **Content** :
* Defines macros, constants, and settings to control how MCAL behaves for a specific application.
* It may include configuration settings like clock frequencies, peripheral initialization data, or interrupt priorities.
* **Example** : If you are configuring a UART peripheral, the `cfg.c` file might contain `#define UART_BAUD_RATE 9600` or other peripheral-specific settings.

### 4. **interface.h**

* **Purpose** : The **interface file** provides the **API (Application Programming Interface)** that will be used by the higher layers (like the HAL or the application layer). It defines the functions that can be called to interact with the microcontroller's peripherals.
* **Content** :
* Function prototypes and API definitions that allow the upper layers to use MCAL services.
* This file abstracts the hardware details from the application, allowing the upper layers to access microcontroller functionality without knowing its exact implementation.
* Typically, this file would include function prototypes for operations such as `void UART_Init(void)` or `void GPIO_SetPin(uint8_t pin, bool state)`.
* **Example** : The `interface.h` file could have definitions like:

<pre class="!overflow-visible" data-start="3291" data-end="3392"><div class="contain-inline-size rounded-md border-[0.5px] border-token-border-medium relative bg-token-sidebar-surface-primary dark:bg-gray-950"></div></pre>

### 5. **prog.c**

* **Purpose** : This file contains the **implementation** of the MCAL functions defined in the interface. It implements the actual functionality of the MCAL in a platform-specific manner.
* **Content** :
* The **function implementations** for the MCAL API declared in the interface.
* This is where the real code resides for interacting with hardware registers, setting up peripherals, and handling interrupts.
* **Example** : If `UART_Init()` is defined in the interface, then the actual code to initialize the UART peripheral would go into `prog.c`. The code would involve setting the baud rate, configuring data bits, enabling interrupts, etc.

---

# HAL Files

It,s the same as MCAL without the register file obviously .



---

**Writing the driver Together .....!**
