use raylib::{drawing::RaylibDraw, ffi::DrawRectangle};

enum Direction {
    North,
    South,
    East,
    West
}



fn part1(data: &str) -> usize {


    let mut grid : Vec<Vec<char>> = Default::default();
    let n = data.split_once("\n").into_iter().nth(0).unwrap().0.len();
    let m = data.lines().count();

    let mut furthest = 0;

    println!("{}", n);
    println!("{}", m);

    grid.resize(n, Default::default());

    for line in &mut grid {
        line.resize(m, '0');
    }

    let mut line = data.lines().enumerate();
    let mut start = [0, 0];
    for l in &mut grid {
        let cs = line.next().unwrap();
        *l = cs.1.chars().collect();
        print!("{}", cs.0);
        for (j, c) in l.iter().enumerate() {
            if *c == 'S' {
                start = [cs.0, j];
            }
            print!("{}", c);
        }
        println!("");
    }

    println!("Starting @ {:?}", start);

    let mut pos = start;
    let mut last_dir : Direction;

    const DIRS : [[i32; 2]; 4] = [
        [1, 0],
        [0, 1],
        [-1, 0],
        [0, -1]
    ];

    loop {
        for d in DIRS {
        }
        if last
    }

    return furthest;
}

fn part2(data: &str) -> usize {

    return 0;
}

#[test]
fn t_part1() {
    assert_eq!(part1(".....
.S-7.
.|.|.
.L-J.
....."), 4);

    assert_eq!(part1("..F7.
.FJ|.
SJ.L7
|F--J
LJ..."), 8);
}

fn main() {



    let content = std::fs::read_to_string("../data.txt").expect("UNable to read file");
    println!("Silver: {}", part1(&content));
    println!("Gold: {}", part2(&content));
}
