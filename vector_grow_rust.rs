/// A (possibly naive) Rust version of the vector benchmark

extern crate time;

use std::os;
use std::iter;

fn main() {
    let args = os::args();
    let n: uint = from_str(args[1].as_slice()).expect("Bad argv");
    let mut v = Vec::new();
    let mut m: [u64, ..101] = [0, ..101];

    let t = time::precise_time_ns();
    for i in iter::range_step(0, n, n/100) {
        for j in range(0, n/100) {
            v.push(j);
        }
        m[i / (n / 100) + 1] = time::precise_time_ns() - t;
    }

    println!("\"size\",\"time\"");
    for (i, t) in m.iter().enumerate() {
        let time = t.to_f32().expect("Bad float conversion")/1000000000.0;
        println!("{},{}", i * (n / 100), time);
    }
}
