use std::{collections::HashMap, sync::atomic};

fn check_totals(totals : Vec<u16>) -> bool {

    let mut capacities = HashMap::new();
    capacities.insert("red", 12);
    capacities.insert("green", 13);
    capacities.insert("blue", 14);

    return  totals[0] <= *capacities.get(&"red").unwrap() &&
            totals[1] <= *capacities.get(&"green").unwrap() &&
            totals[2] <= *capacities.get(&"blue").unwrap()
}

fn possible_set(line: &str) -> usize {

    let parts : Vec<_> = line.split(":").collect();
    let header : Vec<_> = parts[0].split(" ").collect();
    let mut id = header[1].parse::<usize>().expect("Unable to parse number");
    let body = &parts[1];

    let sets : Vec<_> = body.split(";").collect();

    for s in &sets {
        let mut totals : Vec<u16> = Vec::new();
        totals.resize(3, 0);
        let cols = s.split(",").map(|col| col.split(" ").filter(|c| *c != "").collect::<Vec<_>>()).collect::<Vec<_>>();

        for c in &cols {
            match c[1] {
                "red" => {
                    totals[0] += c[0].parse::<u16>().unwrap();
                },
                "green" => {
                    totals[1] += c[0].parse::<u16>().unwrap();
                },
                "blue" => {
                    totals[2] += c[0].parse::<u16>().unwrap();
                },
                _ => ()
            }
        }
        if !check_totals(totals) {
            id = 0;
        }
    }
    return id;
}

fn get_min_cubes_sqr(line: &str) -> usize {
    let parts : Vec<_> = line.split(":").collect();
    let body = &parts[1];
    let sets : Vec<_> = body.split(";").collect();
    let mut min_viable : Vec<u16> = Vec::new();
    min_viable.resize(3, 0);

    let mut min_sum = 0;
    for s in &sets {
        let cols = s.split(",").map(|col| col.split(" ").filter(|c| *c != "").collect::<Vec<_>>()).collect::<Vec<_>>();

        for c in &cols {
            match c[1] {
                "red" => {
                    min_viable[0] = std::cmp::max(c[0].parse::<u16>().unwrap(), min_viable[0]);
                },
                "green" => {
                    min_viable[1] = std::cmp::max(c[0].parse::<u16>().unwrap(), min_viable[1]);
                },
                "blue" => {
                    min_viable[2] = std::cmp::max(c[0].parse::<u16>().unwrap(), min_viable[2]);
                },
                _ => ()
            }
        }
    }
    min_sum += min_viable[0] * min_viable[1] * min_viable[2];
    return min_sum.into();
}

fn part2(content: &str) -> usize {

    let lines = content.lines();
    let mut min_sum = 0;
    for l in lines {
        min_sum += get_min_cubes_sqr(l)
    }
    return min_sum;
}

fn part1(content:&str) -> usize {

    let lines = content.lines();
    let mut sum = 0;

    for l in lines {
        sum += possible_set(l);
    }

    return sum;
}
#[test]
fn t_part2() {
    assert_eq!(part2("Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 greenGame
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"), 2286);
}

#[test]
fn t_part1() {
    assert_eq!(part1("Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 greenGame
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"), 8);
}

fn main() {
    let data = std::fs::read_to_string("../data").expect("Unable to read file.");
    println!("Part1: {}", part1(&data));
    println!("Part2: {}", part2(&data));
}
