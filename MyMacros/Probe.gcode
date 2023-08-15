; Probe Cycle
G90 G58 F1000 Z0            ; Move to top Z position in WCO G58
G10 L20 P4 Z0               ; Set current position Z (WCO) to 0 so max travel is known
G90 G57 F1000 X0 Y0         ; Move to probe postion X=0,Y=0 in WCO G57
G91 G38.2Z-100F500P52.15    ; Probe (sensor height 52 mm)
G0 G90 F500 Z60             ; Clear the probe and move to know position 60 mm above table
G10 L20 P1 Z41              ; Set workoffset Z (G54), 19 mm from G57 (60-19=41)              
G90 G58 F1000 Z0            ; Move to Z top position in WCO G58
G90 G54 X0 Y0               ; Move to X0, Y0 in WCO G54

;G90 G58 F1000 Z0;G10 L20 P4 Z0;G90 G57 F1000 X0 Y0;G91 G38.2Z-100F500P52.15;G0 G90 F500 Z60;G10 L20 P1 Z41;G90 G58 F1000 Z0;G90 G54 X0 Y0