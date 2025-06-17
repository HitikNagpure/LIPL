# Problem Statement 2 – nPM1100 Evaluation Board Design

This submission contains a reference PCB design for the **Nordic nPM1100** Power Management IC, created as part of the LIPL Embedded Systems Intern Assessment.

---

## 🎯 Objective

- Design a 3.0V output evaluation board using the **nPM1100-QDAB-R7** (QFN24 package).
- Include battery charging and voltage measurement functionality.
- Interface with host MCU via pin headers.
- Use only top-mounted SMD components (0403 to 0805).
- Provide required documentation in PDF and CSV formats.

---

## 🔧 Tools Used

**KiCad 9.0 (Open-source PCB design suite)
**SnapEDA/SnapMagic** (for symbol and footprint imports)
**LCSC** (for BOM part sourcing)
**ChatGPT and AI tools** (for learning, guidance, and troubleshooting)


## 🧪 Design Summary

**Output Voltage:** 3.0V (configured using external resistors)
**Charge Current:** 200 mA
**Battery Voltage Measurement:** Included using a voltage divider connected to MCU ADC
**Power & Charging LEDs:** Status indication via GPIO pins
**Host Interface:** I2C lines and status outputs connected to pin headers
**Power Input:** 5V via 2-pin header (assumed ripple-free, 1A capable)

---

## 💡 My Experience

This was my **first time working with any PCB design software**.

Originally, I had planned to learn **KiCad** or **Eagle** later — but this assessment pushed me to start immediately. I spent the first day learning about:

- Schematics
- PCB layout and routing
- BOM generation
- What Gerber files are

And the next day, I started designing in KiCad.

Using **ChatGPT and other AI tools** helped me learn quickly and confidently. From understanding schematic tools to solving practical doubts, AI tools were like a **real-time mentor** during this project. The experience was challenging at first but ultimately **fun, empowering, and productive**.

---

## ✅ Evaluation Criteria Checklist

- [x] Clean and labeled schematic ✅
- [x] Proper PCB layout ✅
- [x] 3.0V output voltage ✅
- [x] 200mA charge current ✅
- [x] Bonus: battery voltage measurement ✅
- [x] All SMD components top-mounted ✅
- [x] PDF and CSV formats (no Gerbers) ✅
- [x] KiCad used (open-source tool) ✅

---

## 🧾 Notes

- PCB size is within the 35mm × 35mm limit.
- Only standard-sized SMD components (0403 to 0805) used.
- BOM includes designators and valid LCSC part numbers.

---

Thank you for reviewing this submission!
