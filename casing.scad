
clearance = 0.2;
cap_clearance = 0.3;
t = 0.01;
$fn = 18;
wall = 1.2;

pcb_w = 61;
pcb_d = 72.5;
pcb_h = 1.6;
height = 10 + wall;

module edgk_35() {
    wire_w = 0.8;
    wire_h = 3.5;
    wire_d = 3.5; // distance between legs
    w = 7.8;
    d = 7.2;
    color("#8D8")
    cube([w, d, 9.2]);
    for (x = [w/2 - wire_d/2, w/2 + wire_d/2]) {
        color("silver")
        translate([x - wire_w/2, 2.9, -wire_h])
        cube([wire_w, wire_w, wire_h]);
    }
}

module pcb(positive, real) {
    c = (real)? 0: clearance;
    w = pcb_w;
    d = pcb_d;
    h = pcb_h;
    screw_hole_from_edge = 1.5;
    screw_hole_d = 3.5;
    screw_hole_pos = screw_hole_from_edge + screw_hole_d/2;
    screw_h = 10;
    if (positive) {
        hole_size = screw_hole_d + screw_hole_from_edge*2;
        color("blue")
        difference() {
            intersection() {
                for (x = [0, w], y = [0, d]) {
                    translate([x, y, -height+wall])
                    cylinder(r = hole_size, h = height-wall);
                    //cube([hole_size, hole_size, height-wall + t*2]);
                }
                translate([-clearance, -clearance, -height+wall])
                cube([w+clearance*2, d+clearance*2, height]);
            }
            // screw holes
            for (x = [screw_hole_pos, w - screw_hole_pos], y = [screw_hole_pos, d - screw_hole_pos]) {
                translate([x, y, -h])
                cylinder(d = 2.4 + c*2, h = h + t*2+c*2);
                translate([x, y, - screw_h])
                cylinder(d = 2, h = screw_h);
            }
        }
    } else {
        translate([0, 0, -h])
        difference() {
            color("orange")
            translate([-c, -c, -c])
            cube([w+c*2, d+c*2, h+c*2]);
            // screw holes
            for (x = [screw_hole_pos, w - screw_hole_pos], y = [screw_hole_pos, d - screw_hole_pos]) {
                translate([x, y, -t-c])
                cylinder(d = screw_hole_d - c*2, h = h + t*2+c*2);
            }
        }
        // dc in
        translate([1.7, 65, 0])
        rotate(90, [0, 0, -1])
        edgk_35();
        // big cap
        color("#333")
        translate([29.8, 55, 0])
        cylinder(d = 8.1, h = 13);
        // big inductor
        color("#333")
        translate([53.6, 24.6, 0])
        cylinder(d = 9.7, h = 14);
        // spacing for bottom smd parts and tht legs
        smd_h = 2.4 + c;
        smd_padding = 0.8;
        color([1, 1, 1, 0.5])
        translate([0, 0, -h - smd_h])
        difference() {
            cube([pcb_w - smd_padding*2, pcb_d - smd_padding*2, smd_h]);
            hole_size = screw_hole_d + screw_hole_from_edge*2;
            for (x = [screw_hole_pos, w - screw_hole_pos], y = [screw_hole_pos, d - screw_hole_pos]) {
                translate([x - hole_size/2, y - hole_size/2, -t])
                cube([hole_size, hole_size, smd_h + t*2]);
            }
        }
    }
}

module upper_casing(positive, real) {
    c = (real)? 0: cap_clearance;
    if (positive) {
    } else {
    }
}

module lower_casing(positive, real) {
    c = (real)? 0: clearance;
    w = pcb_w + clearance*2 + wall*2;
    d = pcb_d + clearance*2 + wall*2;
    h = height;
    pcb_pos = [wall + clearance, wall + clearance, h];
    cap_pos = [0, 0, h];
    cavity_margin = wall + 5;
    if (positive) {
    } else {
        difference() {
            union() {
                color("#555")
                difference() {
                    cube([w, d, h]);
                    // cavity
                    translate([wall+c, wall+c, wall+c])
                    cube([w - wall*2 -c*2, d - wall*2 - c*2, h - wall + t]);
                }
                translate(cap_pos)
                upper_casing(true, true);
                translate(pcb_pos)
                pcb(true, true);
            }
            /*translate([cavity_margin, cavity_margin, wall])
            cube([w - cavity_margin*2, d - cavity_margin*2, h - wall + t]);*/
            translate(cap_pos)
            upper_casing(false, false);
            // pcb imprint
            translate(pcb_pos)
            pcb(false, false);
        }
        *translate(pcb_pos)
        pcb(false, true);
    }
}

lower_casing(false, true);