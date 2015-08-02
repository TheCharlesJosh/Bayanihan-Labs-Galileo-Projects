$fn = 30;

resize([9,0,0], auto=true) difference() {
    translate([-4,-4,-2.5]) cube([8,8,10]);
    union() {
        intersection() {
            translate([0,0,-(2.29/2)]) cylinder(h=10, r=4.88/2.05);
            translate([-4.88/2,-3.8/2,-2.29/2]) cube([4.88,3.8,10]);
        }

        translate([2.69/2,0,-49]) cylinder(h=50, r=0.6);
        translate([-2.69/2,0,-49]) cylinder(h=50, r=0.6);
    }
}