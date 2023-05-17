include <polyScrewThread_r1.scad>

full = true;
fnval = 120;



module cylinder_nut(df,hg,sth,clf,cod,crs){  
  hex_countersink_ends(sth/2,cod,clf,crs,hg);
  screw_thread(cod,sth,clf,hg,crs,-2);
}

module triangleR(a, b, h, c){
  linear_extrude(height = h, center = c, convexity = 10)
  resize([a, b])
  polygon([[0,0], [1,0], [0,1]], paths=[[0,1,2]]);
}

module triangleRa(a, angle, h, c){
  rotate([90, 0, 0])
  linear_extrude(height = h, center = c, convexity = 10)
  resize([a, a*tan(angle)])
  polygon([[0,0], [1,0], [0,1]], paths=[[0,1,2]]);
}

module triangleI(x, y, z, c){
  rotate([90, 0, 0])
  linear_extrude(height = y, center = c, convexity = 10)
  resize([x, z])
  polygon([[-1,0], [1,0], [0,1]], paths=[[0,1,2]]);
}


module bucket2(){
  difference(){
    union(){
      difference(){
        triangleI(70, 20, 25, true);
        
        translate([-70/4-1/2, 0, (25+2)/2]) cube([70/2, 20-4, 25-2], center = true);
        translate([70/4+1/2, 0, (25+2)/2]) cube([70/2, 20-4, 25-2], center = true);
      }
      
      triangleI(20, 20, 15, true);
    }
    
    translate([0, 0, 3]) rotate([90, 0, 0]) cylinder(d=3.25, h=20, center=true, $fn=30);
  }
  
  //magnet
  translate([0, 10+2/2, 21])
  rotate([90, 0, 0])
  difference(){
    cylinder(d=6.25, h=2, center=true, $fn=30);
    cylinder(d=4.25, h=2, center=true, $fn=30);
  }  
}

module bucket(){
  difference(){
    union(){
      difference(){
        triangleI(70, 20, 25, true);
        
        translate([-70/4-1/2, 0, (25+1)/2]) cube([70/2, 20-2, 25-1], center = true);
        translate([70/4+1/2, 0, (25+1)/2]) cube([70/2, 20-2, 25-1], center = true);
      }
      
      triangleI(25, 20, 15, true);
    }
    
    translate([0, 0, 3]) rotate([90, 0, 0]) cylinder(d=3.25, h=20, center=true, $fn=30);
  }
  
  //magnet
  translate([0, 10+2/2, 21])
  rotate([90, 0, 0])
  difference(){
    cylinder(d=6.25, h=2, center=true, $fn=30);
    cylinder(d=4.25, h=2, center=true, $fn=30);
  }  
}

module base(){
  translate([0, 0, -5/2])
  difference(){
    cylinder(d=120, h=5, center=true, $fn=fnval);
    
    //water holes
    for(dy = [-2:1:2], dx = [-1, 0, 1]){
      translate([-39*dx, 5*dy, 0]) cube([14, 4, 5], center = true);
    }  

    for(dy = [-1:1:1]){
      translate([0, 6*dy-35, 0]) cube([30, 4, 5], center = true);
    }    
    
    for(dy = [-1:1:1], dx = [-1, 1]){
      translate([10*dx, 6*dy+35, 0]) cube([10, 4, 5], center = true);
    }   
    
    //screw holes
    for(dx = [-1,1], dy = [-1, 1]){
      translate([30*dx, 30*dy, 0]) cylinder(d=4.25, h=5, center=true, $fn=30);
    }
    
    //cable hole
    translate([0, 31, 0]) cube([5, 8, 5], center = true);
  }
  
  //screw holes
  for(dx = [-1,1], dy = [-1, 1]){
    translate([30*dx, 30*dy, 0]) 
    difference(){
      cylinder(d=12, h=5, center=false, $fn=30);
      cylinder(d=4.25, h=5, center=false, $fn=30);
      translate([0, 0, 5-3]) cylinder(d=8, h=3, center=false, $fn=30);
    }
  }
  
  //cable holder
  translate([0, 31+8/2+10/2, 20/2]) cube([8, 10, 20], center = true);
  
  //border
  translate([0, 0, 16/2])
  difference(){
    cube([92+2*2, 24+2*2, 16], center = true);
    cube([92, 24, 16], center = true);
  }
   
  
  //holder
  difference(){
    translate([0, 0, 18/2+1/2]) cube([12, 20+2*2+2*5, 19], center = true);
    
    translate([0, 0, 18/2]) cube([12, 20+2*2, 20], center = true);
    translate([0, 0, 18]) rotate([90, 0, 0]) cylinder(d=3.25, h=20+2*2+2*3, center=true, $fn=30);
  }
  
  //stop
  difference(){
      for(dx = [-1, 1]) {
        translate([22*dx, 0, 3]) scale([dx, 1, 1]) {
          translate([10/2, 0, -3/2]) cube([10, 24, 3], center = true);
          triangleRa(10, 20, 24, true);
        }
      }
      translate([0, 0, 10/2]) cube([70, 20-2*2, 10], center = true);
  }
  
  //pcb holder  
  translate([0, 19, 16/2])
  difference(){
    cube([50, 10, 16], center = true);
    cube([40, 4, 16], center = true);
  }
  
  
  //thread  
  if(full){
    difference(){
      translate([0, 0, 0]) screw_thread(105, 4, 55, 12, PI/2, 2);
      cylinder(d=96, h=14, center=false, $fn=fnval);
    }
  }
  else{
    difference(){
      cylinder(d=105, h=14, center=false, $fn=fnval);
      cylinder(d=96, h=14, center=false, $fn=fnval);
    }
  }
    
  
}

module funnel(){
  
  difference(){
    union(){
      translate([0, 0, 120])
      mirror([0, 0, 1])
      rotate_extrude(angle = 360, convexity = 2, $fn=fnval)
      difference(){
        resize([10*sqrt(100/PI)+2, 70+2])  polygon([[0,0], [1,0], [0,1]], paths=[[0,1,2]]);
        resize([10*sqrt(100/PI), 70])  polygon([[0,0], [1,0], [0,1]], paths=[[0,1,2]]);
      }
            
      difference(){
        cylinder(r=10*sqrt(100/PI)+2, h=120, center=false, $fn=fnval);
        cylinder(r=10*sqrt(100/PI), h=120, center=false, $fn=fnval);
      }
      
      
      translate([0, 0, 120-70-10+2.5]) cylinder(d=7, h=10, center=false, $fn=30);
    }
    translate([0, 0, 120-70-10+2.5]) cylinder(d=5, h=10, center=false, $fn=30);
  }
  
  difference(){
    translate([0, 0, 14/2]) cylinder(r=10*sqrt(100/PI), h=14, center=true, $fn=fnval);
    if(full){
      cylinder_nut(100, 14, 4, 55, 105.5, 0.5);
    }
    else{
      translate([0, 0, 14/2]) cylinder(d=105.5, h=14, center=true, $fn=fnval);
    }
  }
  
  translate([0, 0, 14+5/2]) 
  difference(){
    cylinder(r=10*sqrt(100/PI), h=5, center=true, $fn=fnval);
    cylinder(r2=10*sqrt(100/PI), r1=105.5/2, h=5, center=true, $fn=fnval);
  }
  
  
}

module sensor(){
    difference(){
        union(){
            translate([0, -0.25/2, 0]) cube([40-0.25, 4-0.25, 55], center = true);
            
            translate([0, -3, 12])
            difference(){
                cube([5, 3, 14], center = true);
                translate([0, -3/2+2.25/2, 0]) cylinder(d=2.25, h=8, center=true, $fn=30);
                translate([0, -3/2+2.25/4, 0]) cube([2.25, 2.25/2, 8], center = true);
                translate([0, -3/2+2.25/4, 0]) cube([0.75, 2.25/2, 12], center = true);
            }
            
        }
                
        translate([0, -1, 12+6-0.5]) cube([1, 8, 1], center = true);
        translate([0, -1, 12-6+0.5]) cube([1, 8, 1], center = true);
        
        translate([0, 1.75/2, 12]) cube([2, 1.75, 20], center = true);
        
        for(dx = [-1, 1]) 
        translate([-10*dx, (3.75-3)/2, 12]) rotate([90, 0, 0]) cylinder(d=2.7, h=3, center=true, $fn=30);
     }
}

module sensor_back(){
    difference(){
        translate([0, 0, 0]) cube([30, 3, 30], center = true);
    
        for(dx = [-1, 1]) 
            translate([-10*dx, 0, 0]) rotate([90, 0, 0]) cylinder(d=3.2, h=5, center=true, $fn=30);

        hull(){
            translate([0, 0, 1]) rotate([90, 0, 0]) cylinder(d=2, h=5, center=true, $fn=30);
            translate([0, 0, -1]) rotate([90, 0, 0]) cylinder(d=2, h=5, center=true, $fn=30);
        }
    }
    
    for(dx = [-1, 1]) 
        translate([-10*dx, (3+2)/2, 0]) rotate([90, 0, 0])
            difference(){
               cylinder(d=10, h=2, center=true, $fn=30);
               cylinder(d=6, h=2, center=true, $fn=30);
            }
    
}

module bending_tool(){
    difference(){
        cube([11, 5, 5], center = true);
        translate([0, 0, 2]) cube([11, 1, 1], center = true);
        translate([0, 0, 2]) cube([8, 2, 2], center = true);
    }
}

module assembled(){
    translate([0, 0, -18])base();
    rotate([0, 0, 0]) translate([0, 0, -3]) bucket();
    translate([0, 19, 55/2-18]) sensor();
    translate([0, 24, 55/2-18+12]) sensor_back();
    translate([0, 0, -18]) funnel();
}

module exploded(){
    translate([0, 0, -18])base();
    rotate([0, 0, 0]) translate([0, 0, 20]) bucket();
    translate([0, 19, 30]) sensor();
    translate([0, 30, 42]) sensor_back();
    translate([0, 0, 70]) funnel();
}

//assembled();

exploded();

//bending_tool();



