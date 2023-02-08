mod Vec {
    pub struct Vec2<T: PartialEq + Copy> {
        x: T,
        y: T
    }
    
    impl<T: PartialEq + Copy> Vec2<T> {
        pub fn new(x: T, y: T) -> Vec2<T> { Vec2{ x: x, y: y } }
    
        pub fn getX(&self) -> T { self.x }
    
        pub fn getY(&self) -> T { self.y }
    
        pub fn setX(&mut self, val: T) { self.x = val; }
    
        pub fn setY(&mut self, val: T) { self.y = val; }
    }
}

fn main() {
    let mut a = Vec::Vec2::new(4, 3);
    a.setX(12);
    println!("Hello World {} {}", a.getX(), a.getY());
}