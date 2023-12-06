

fn part1(data: &str) -> usize {

    let races : Vec<_> = data.lines().collect();

    let times : Vec<usize> = races[0].split_whitespace().skip(1).map(|n| n.parse::<usize>().unwrap()).collect();
    let distances : Vec<usize> = races[1].split_whitespace().skip(1).map(|n| n.parse::<usize>().unwrap()).collect();
    let mut wins : Vec<usize> = Default::default();
    wins.reserve(times.len());

    for i in 0..times.len() {
        let mut acc = 0;
        for ms in 1..=times[i] {
            let speed = ms;
            let time_left = times[i] - ms;
            let travelled = time_left * speed;
            if travelled > distances[i] {
                acc += 1;
            }
        }
        wins.push(acc);
    }
    return wins.iter().product();

}

fn part2(data: &str) -> f64 {
    
    let races : Vec<_> = data.lines().collect();
    let time = races[0].split_whitespace().filter(|c| *c != " ").skip(1).collect::<Vec<&str>>().join("").parse::<f64>().unwrap();
    let distance = races[1].split_whitespace().filter(|c| *c != " ").skip(1).collect::<Vec<&str>>().join("").parse::<f64>().unwrap();

    let r1 = (-time - (((time * time) - 4.0 * distance)).sqrt()) / -2.0;
    let r2 = (-time + (((time * time) - 4.0 * distance)).sqrt()) / -2.0;
    return r1.ceil() - r2.floor() - 1.0;
}

#[test]
fn t_part1() {
    assert_eq!(part1("Time:      7  15   30
Distance:  9  40  200"), 288);
}
#[test]
fn t_part2() {
    assert_eq!(part2("Time:      7  15   30
Distance:  9  40  200") as usize, 71503);
}

fn main() {

    let content = std::fs::read_to_string("../data.txt").expect("Unable to read data file");

    // println!("Part1 : {}", part1(&content));
    println!("Part2 : {}", part2(&content));
}
