use std::collections::HashSet;

use rustc_hash::FxHashSet;


fn process(line: &str, wins: &mut FxHashSet<usize>) -> usize {

    let ans : Vec<Vec<usize>> = line.split(":").collect::<Vec<_>>()[1].split("|")
        .map(|h| h
             .split(" ")
             .into_iter()
             .filter(|c| *c != "")
             .into_iter()
             .map(|s: &str| s.parse::<usize>().unwrap()).collect::<Vec<usize>>())
        .collect();

    let mut n_matches = 0;
    wins.extend(ans[0].iter().copied());
    for g in ans[1].clone() {
        n_matches += usize::from(wins.contains(&g));
    }
    wins.clear();
    return n_matches;
}

fn part2(data: &str) -> usize {

    let lines = data.lines().collect::<Vec<_>>();
    let mut totals : Vec<usize> = Vec::new();
    totals.resize(lines.len(), 1);

    let mut wins : FxHashSet<usize> = Default::default();

    for i in 0..data.lines().count() {
        let matches_per_card : usize = process(lines[i], &mut wins);
        let range = i+matches_per_card;

        if i > range {
            continue;
        }
        for j in i+1..=range {
            if j == totals.len() {
                break;
            }
            totals[j] += totals[i];
        }

    }
    return totals.into_iter().sum();
}

fn part1(data: &str) -> usize {

    let cont : Vec<_> = data.lines().collect();

    let mut result = 0;

    for i in cont {
        let halves : Vec<_> = i[9..].split("|").collect();

        let winners = halves[0].split(" ").filter(|c| *c != "").into_iter().map(|s: &str| s.parse::<usize>().unwrap()).collect::<Vec<usize>>();
        let guesses = halves[1].split(" ").filter(|c| *c != "").into_iter().map(|s: &str| s.parse::<usize>().unwrap()).collect::<Vec<usize>>();

        let mut winnings = 0;

        for g in &guesses {
            for w in &winners {
                if g == w {
                    if winnings > 0 {
                        winnings = winnings * 2;
                    } else {
                        winnings = 1;
                    }

                }
            }
        }

        result += winnings;
    }

    return result;
}

#[test]
fn t_part2() {
    assert_eq!(part2("Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11"), 30);
}

fn main() {
    let content = std::fs::read_to_string("../bigboy.txt").expect("Unable to read file");
    // println!("Part1: {}", part1(&content));
    println!("Part2: {}", part2(&content));
}
