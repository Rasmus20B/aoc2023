use std::fs;

fn add_first_and_last_digits(data: &str) -> usize {
    let nums : String = data.chars().filter(|c| c.is_digit(10)).collect(); 
    let a = (nums.as_bytes()[0] as char).to_digit(10).unwrap();
    let b = (nums.as_bytes()[nums.len() - 1] as char).to_digit(10).unwrap();
    let incr = a * 10 + b;

    incr as _
}

fn part1(data: &str) -> usize {

    let mut res = 0;

    for l in data.lines() {
        res += add_first_and_last_digits(l);
    }
    res as _
}

fn part2(data: &str) -> usize {

    const DIG_VALS : [(&str, usize); 9] = [ 
        ("one", 1),
        ("two", 2),
        ("three", 3),
        ("four", 4),
        ("five", 5),
        ("six", 6),
        ("seven", 7),
        ("eight", 8),
        ("nine", 9)
    ];

    let mut sum : usize = 0;
    for l in data.lines() {
        let mut new_line = String::new();
        for i in 0..l.len() {
            let mut found = false;
            for (dig, val) in DIG_VALS {
                if l[i..].starts_with(dig) {
                    found = true;
                    new_line.push_str(&val.to_string());
                    break;
                }
            }

            if !found {
                new_line.push_str(&l[i..i+1].to_string());
            }
        }
        sum += add_first_and_last_digits(&new_line);
    }
    return sum;
}

#[test]
fn t_part1() {
    let test = "1abc2
                pqr3stu8vwx
                a1b2c3d4e5f
                treb7uchet";
    assert_eq!(part1(test), 142);
}

#[test]
fn t_part2() {
    let test = "two1nine
                eightwothree
                abcone2threexyz
                xtwone3four
                4nineeightseven2
                zoneight234
                7pqrstsixteen";
    assert_eq!(part2(test), 281);
}


fn main() {
    
    let path = "../bigboy";
    let content = fs::read_to_string(path).expect("Could not read file");

    println!("part1: {}", part1(&content));
    println!("part2: {}", part2(&content));
}
