$fn = 30;

resize([11,0,0], auto=true) intersection() {
    cylinder(h=15, r=6.2, center=true);
    difference() {
        cube([10,10,10], center=true);
        union() {
            cylinder(h=10, r=2.5, center=true);
            translate([0,0,-6]) cylinder(h=3, r=3);
        }
    }
}