# Linux Kernel Timer Module

## Overview

This project demonstrates a simple Linux Kernel Module (LKM) that uses
the Linux kernel timer subsystem to execute a function periodically.

The module:

- Registers a kernel timer
- Accepts a module parameter `interval`
- Prints periodic messages to kernel log (dmesg)
- Can be inserted and removed dynamically

This is useful for understanding:

- Kernel module lifecycle
- Timer APIs in Linux kernel
- Module parameters
- Secure Boot module signing
- Kernel logging

---

## Main Theory

### 1. What is a Linux Kernel Module?

A Linux Kernel Module (LKM) is a dynamically loadable piece of kernel
code that extends kernel functionality without rebooting the system.

Commands:

- `insmod` → Insert module
- `rmmod` → Remove module
- `lsmod` → List loaded modules

---

### 2. Kernel Timer Concept

Linux provides `struct timer_list` to execute code after a specific time.

Typical flow:

1. Initialize timer
2. Set expiration time (in jiffies)
3. Register callback function
4. Re-arm timer if periodic execution is required

Jiffies = Kernel time unit (ticks)

---

### 3. Module Parameter

This module accepts:

```
interval=<seconds>
```

This defines how frequently the timer fires.

Example:

```
sudo insmod timer_module.ko interval=2
```

This means:
Timer callback runs every 2 seconds.

---

### 4. Secure Boot & Module Signing

Modern Linux systems with Secure Boot enabled require
kernel modules to be signed.

Command used:

```
sudo /usr/src/linux-headers-$(uname -r)/scripts/sign-file sha256 \
~/kernel_keys/MOK.key \
~/kernel_keys/MOK.crt \
timer_module.ko
```

Explanation:

- `sha256` → Hash algorithm
- `MOK.key` → Private key
- `MOK.crt` → Public certificate
- `timer_module.ko` → Module to sign

This ensures the kernel trusts the module.

---

## Build Instructions

```
make
```

Requires:
- Kernel headers installed
- Build tools

---

## Insert Module

```
sudo insmod timer_module.ko interval=2
```

---

## View Kernel Logs

```
dmesg | tail
```

---

## Remove Module

```
sudo rmmod timer_module
```

---

## Learning Outcomes

After studying this module, you should understand:

- Kernel module structure
- init and exit macros
- Kernel timers
- Jiffies and HZ
- Secure Boot signing process
- Kernel logging via printk

---
