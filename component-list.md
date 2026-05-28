# Electronics component list

Bill of materials for the Arduino control side of the liquid cooling suit. Values match the [control shield schematic](arduino-shield/arduino-shield.pdf). KiCad source files in `arduino-shield/` are maintained separately and are not edited from this repo workflow.

**Assembly goal:** stack shields on an **Arduino Uno R3** with **minimum soldering** — plug-in headers and screw terminals for field wiring; only populate/solder the control shield PCB if you order it bare. If you are new to soldering, see [Soldering and wire splicing](#soldering-and-wire-splicing) below.

## Table of contents

- [Stack (bottom to top)](#stack-bottom-to-top)
- [Core components](#core-components)
- [Control shield](#control-shield-included-in-stack)
- [Ordering the PCB from Gerber files](#ordering-the-pcb-from-gerber-files)
- [Wire and cable](#wire-and-cable-minimum-soldering)
- [Soldering and wire splicing](#soldering-and-wire-splicing)
  - [How to solder (NASA reference)](#how-to-solder)
  - [How to splice wire properly](#how-to-splice-wire-properly)
  - [Heat-shrink on splices](#heat-shrink-on-splices)
- [Quick wiring reference](#quick-wiring-reference)
- [Suggested order checklist](#suggested-order-checklist)
- [12 V safety and enclosure](#12-v-safety-and-enclosure)

---

## Stack (bottom to top)

| Layer | Part | Notes |
| --- | --- | --- |
| 1 | **Arduino Uno R3** | ATmega328P, 5 V logic. Powers from 12 V barrel jack or VIN when on battery. |
| 2 | **Heatsink control shield** | [arduino-shield.pdf](arduino-shield/arduino-shield.pdf) — Q1/Q2, R1, TH1 header, SW1–SW3 headers, buzzer, 12 V pump/spare terminals. Solder only if you receive a bare PCB. |
| 3 | **LCD shield (no buttons)** | 20×4 HD44780, **display only** — no keypad, no built-in push-buttons. Plugs onto the stack; uses D5, D6, D10–D13 (see [pin summary](readme.md#pin-summary)). Do **not** use an LCD Keypad Shield — firmware uses external panel switches on D2–D4. |

External to the stack (crimp or screw terminals, no board soldering): **three panel switches**, **Bosch M12 NTC** cable to TH1 header, **12 V** pump and power leads.

---

## Core components

| Qty | Ref | Description | Part number / spec | Notes |
| --- | --- | --- | --- | --- |
| 1 | U1 | Microcontroller | **Arduino Uno R3** | Required for direct shield stacking. |
| 1 | — | LCD shield | **20×4 HD44780 LCD shield, no buttons** | e.g. parallel “LCD2004” shield without keypad. Display-only — temp/PWM/alarm text; switches stay on the panel. |
| 1 | TH1 | NTC temperature sensor | **Bosch M12** NTC | [Datasheet (70101387)](https://www.bosch-motorsport.com/content/downloads/Raceparts/Resources/pdf/Data%20sheet_70101387_Temperature_Sensor_NTC_M12.pdf). Mount in **collection manifold** at the suit (return path), not in the ice box. Requires **M12 tap** and sealant on metal manifold. |
| 1 | R1 | Fixed resistor, top of NTC divider | **50 kΩ**, 1/4 W or 1/2 W, **1%** metal film | Example: MFP50SBBE52-50K (or equivalent). On control shield between AREF rail and A0; TH1 from A0 to GND. |
| 2 | Q1, Q2 | NPN Darlington, low-side switch | **TIP120** (TO-220) | Q1: pump on **D9** (PWM, up to **5 A**). Q2: spare 12 V on **D8**. Mount to shield **copper thermal zones** — no add-on heatsinks. |
| 2 | SW1, SW2 | Panel switch, momentary | **100SP4T1B2M2QE** | Temp up (D2) and temp down (D3). **Switch guard** recommended (see below). |
| 1 | SW3 | Panel switch, maintained toggle | **ANT13SECQE** | Pump manual/auto on **D4**. **Switch guard** strongly recommended — prevents accidental pump override. |
| 3 | — | Switch guard | Compatible with **100SP** / **ANT** panel switches | Optional but recommended: covers/guards that block accidental bumps (especially on SW3). Match guard to switch series and actuator type per supplier catalog. |

---

## Control shield (included in stack)

| Qty | Description | Notes |
| --- | --- | --- |
| 1 | **Heatsink control shield** PCB | Order assembled if you want zero soldering; otherwise solder TIP120 (to copper thermal zones), R1, buzzer, and headers once. |
| 1 | Buzzer (on shield) | TDK PS1240P02BT class, 12 mm, polarized — alarm on **D7** (>30 °C for 2 min). |

See [Ordering the PCB from Gerber files](#ordering-the-pcb-from-gerber-files) to have bare boards fabricated.

---

## Ordering the PCB from Gerber files

Production-ready Gerbers for the heatsink control shield are in the repo — you do **not** need KiCad to order boards. Use the files in:

**[`arduino-shield/gerbers/`](arduino-shield/gerbers/)**

### What is in the folder

| File | Purpose |
| --- | --- |
| `arduino-shield-F_Cu.gbr` | Top copper |
| `arduino-shield-B_Cu.gbr` | Bottom copper |
| `arduino-shield-F_Mask.gbr` / `B_Mask.gbr` | Solder mask (top / bottom) |
| `arduino-shield-F_Silkscreen.gbr` / `B_Silkscreen.gbr` | Silkscreen legend |
| `arduino-shield-F_Paste.gbr` / `B_Paste.gbr` | Solder paste (for SMT assembly only — ignore if you hand-solder) |
| `arduino-shield-Edge_Cuts.gbr` | Board outline |
| `arduino-shield-PTH.drl` | Plated through-hole drill hits |
| `arduino-shield-NPTH.drl` | Non-plated holes (if any) |
| `arduino-shield-job.gbrjob` | Job metadata (layer stack, thickness) — optional but helps some fabs |

Board spec from the job file: **2-layer FR4**, **1.6 mm** thick, outline roughly **92 × 61 mm** (Arduino Uno R3 shield form factor).

### How to submit to a PCB fab

1. **Download or clone** the repo and open `arduino-shield/gerbers/`.
2. **Select all** `.gbr` and `.drl` files in that folder (include both drill files).
3. **Zip** them into one archive (e.g. `arduino-shield-gerbers.zip`). Keep filenames unchanged — do not nest an extra subfolder unless the fab asks for it.
4. **Upload** the zip to a board house (e.g. JLCPCB, PCBWay, OSH Park, Aisler, or any fab that accepts standard Gerber + Excellon drill).
5. **Preview** the upload in the fab’s Gerber viewer before paying. Check outline, drill hits, and silkscreen alignment.
6. **Choose fab options** (typical for this board):

   | Option | Recommended |
   | --- | --- |
   | Layers | **2** |
   | Thickness | **1.6 mm** |
   | Material | **FR4** |
   | Copper weight | **1 oz** (default) |
   | Surface finish | **HASL** or **ENIG** (either is fine for through-hole) |
   | Solder mask | Any colour (default green is fine) |
   | Silkscreen | White or yellow on green mask |
   | PCB assembly / SMT | **No** — this shield is **through-hole**; you populate it yourself (see [Soldering and wire splicing](#soldering-and-wire-splicing)) |

7. **Quantity:** most fabs quote from **5 pcs** upward; one board is enough for a single suit, extras are spares.

### After the boards arrive

- Compare the bare PCB to [arduino-shield.pdf](arduino-shield/arduino-shield.pdf).
- Solder TIP120 (Q1, Q2) to the **copper thermal zones**, R1, buzzer, Arduino stack headers, and connectors per the schematic PDF.
- Stack on the Uno, add the LCD shield, then wire panel switches and 12 V externally.

### Regenerating Gerbers (optional)

The committed Gerbers match the shield design at export time. To produce a new set you need **KiCad 9** and the project in `arduino-shield/` — open `arduino-shield.kicad_pcb`, run **File → Fabrication Outputs → Gerbers**, and plot to `gerbers/` with drill files included. Only do this if you maintain your own fork of the PCB; the repo’s `gerbers/` folder is the canonical release for ordering.

---

## Wire and cable (minimum soldering)

| Use | Spec | Length (typical) | Notes |
| --- | --- | --- | --- |
| **12 V power** — battery to Uno/shield, pump (+) via Q1, spare via Q2 | **1.5 mm²** (16 AWG) stranded, **≥5 A** | Container ↔ battery ↔ pump | Land on shield **screw terminals**. **5 A inline fuse** per branch. |
| **Pump return / load (−)** | Same as 12 V power | Same | Low-side through Q1/Q2; common GND bus. |
| **Panel switches SW1–SW3** | **0.5 mm²** (22 AWG) stranded | ~0.5–2 m per switch | **Crimp to 1×3 socket** on shield headers — no soldering at panel if you use pre-crimped leads. Wire **pin → switch → GND**. |
| **NTC (TH1)** | **0.5 mm²** twisted or shielded pair | Manifold → control box | Plug or screw to TH1 connector on shield; route away from pump motor and PWM power runs. |
| **Stack interconnect** | — | — | Uno ↔ control shield ↔ LCD shield: **no extra wires** when using standard R3 headers. |

**Connectors:** 1×3 **2.54 mm** socket housings + crimp pins for SW1–SW3; screw terminals on shield for 12 V and pump.

---

## Soldering and wire splicing

**Tools and consumables:**

- **20 W soldering iron** with a fine tip — enough for this PCB and signal wiring, not heavy power lugs
- **Proper solder** — rosin-core electrical solder (e.g. **60/40 tin/lead** or lead-free **Sn96.5**), fine diameter (~0.6–0.8 mm) for through-hole parts and splices
- **Wet sponge** for tip cleaning (keep it damp, not dripping) — standard bench practice alongside the NASA video below
- **Heat-shrink tubing** — **required on every soldered splice** (see below; not shown in the splice reference video)

If you order a **bare** control shield PCB, you will need to solder the through-hole parts (TIP120, R1, buzzer, headers). Panel and 12 V wiring can mostly use **crimps and screw terminals**; any soldered splices must use proper technique **and** heat-shrink insulation so joints stay reliable and safe under vibration and humidity.

### How to solder

NASA training video — old but the workmanship standard is excellent:  
[https://www.youtube.com/watch?v=_RXugDd0xik](https://www.youtube.com/watch?v=_RXugDd0xik)

### How to splice wire properly

[https://www.youtube.com/watch?v=O-ymw7d_nYo](https://www.youtube.com/watch?v=O-ymw7d_nYo)

### Heat-shrink on splices

The splice video does **not** show finishing the joint — after soldering, **slide heat-shrink over the splice and shrink it fully** so no bare copper is exposed. Use tubing sized for your wire (typically slightly larger ID before shrinking); for 12 V runs, use heavier wall or double-layer shrink if the splice is in the harness. No exceptions for in-box or panel wiring.

Prefer **screw terminals or crimp connectors** on 12 V and switch runs where you can and skip splices entirely. When you must splice, follow the [splice video](#how-to-splice-wire-properly), then **always** heat-shrink. Work **de-energized** — battery disconnected and fuses out — see [12 V safety and enclosure](#12-v-safety-and-enclosure).

---

## Quick wiring reference

```
Stack:  Uno R3  →  control shield  →  LCD shield (no buttons)

AREF — R1 (50K) — A0 — TH1 (Bosch M12) — GND   (on control shield)

SW1/SW2/SW3:  header pin → switch → GND  (D2 / D3 / D4)  + switch guards

D9 → Q1 → pump (+)     pump (−) → GND
D8 → Q2 → spare load
D7 → buzzer
```

---

## Suggested order checklist

- [ ] Arduino Uno R3  
- [ ] Heatsink control shield — order bare PCB from [Gerber files](component-list.md#ordering-the-pcb-from-gerber-files) or populate one you already have  
- [ ] LCD shield 20×4 **without buttons**  
- [ ] 1× Bosch M12 NTC + M12 tap + thread sealant  
- [ ] 2× 100SP4T1B2M2QE + guards  
- [ ] 1× ANT13SECQE + guard  
- [ ] 12 V wire (1.5 mm²) + switch leads (0.5 mm²) + crimp housings + fuses (5 A)  
- [ ] **20 W soldering iron**, **rosin-core solder**, **wet sponge**, and **heat-shrink tubing** (only if populating a bare control shield or making splices) — see [Soldering and wire splicing](component-list.md#soldering-and-wire-splicing)

---

## 12 V safety and enclosure

- **Control unit** (Uno + heatsink shield + LCD stack, battery, and dry-side wiring) must stay **dry** — mount in a project box on the harness or pack, **not** inside the ice cooler.
- **Fused 12 V** (5 A max per branch), **1.5 mm²** pump feeds, correct polarity, common ground — see [12V DC safety and dry locations](readme.md#12v-dc-safety-and-dry-locations) in the readme.
- Only the **submersible pump** and coolant path belong in the wet zone; seal lid glands for hose and pump power; keep NTC connector and Arduino wiring in the dry enclosure.
