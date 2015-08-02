use <rack_and_pinion.scad>
$fn = 30;

difference() {
    resize([33,0,0], auto=true) translate([0,0,12]) difference() {
        translate([0,0,-3]) cube([35,15,18], center=true);
        translate([0,0,2]) difference(){
            rotate([90,0,0]) cylinder(h=30, r=12.2, center=true);
            union() {
                translate([0, 0, 18]) cube([80,40,18], center=true);
                translate([0, 0, -18]) cube([80,40,18], center=true);
            }
        }
    }
    translate([0,0,-1]) intersection() {
        translate([-5,-7.5,0]) cube([10,15,4]);
        translate([0,0,-5]) pinion(0.308,50,10,0);
    }
}