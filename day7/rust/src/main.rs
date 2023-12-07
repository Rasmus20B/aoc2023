use std::{collections::HashMap, alloc::handle_alloc_error};

enum HandType {
    FiveKind = 7000000,
    FourKind = 600000,
    FullHouse = 50000,
    ThreeK = 4000,
    TwoPair = 300,
    OnePair = 20,
    High = 1
}

fn get_groups(hand: &mut Vec<usize>) -> Vec<(usize, usize)> {
    
    let mut buckets : Vec<(usize, usize)> = Vec::new();
    buckets.reserve(5);

    for card in &mut *hand {
        let mut found = false;
        for exist in &mut buckets {
            if exist.0 == *card {
                exist.1 += 1;
                found = true;
                break;
            }
        }
        if found == false {
            buckets.push((*card, 1));
        }

    }

    buckets.sort_by(|b1, b2|  b2.1.partial_cmp(&b1.1).unwrap());
    buckets.sort_unstable_by_key(|b|  (b.1, b.0));
    buckets.reverse();

    return buckets;

}

fn get_hand_type(hand: &mut Vec<usize>) -> (Vec<usize>, usize) {

    let buckets = get_groups(hand);
    let col : Vec<_> = buckets.iter().map(|n| n.1).collect();
    let hand_type = match col[..] {
        [1, 1, 1, 1, 1] => 7,
        [2, 1, 1, 1] => 6,
        [2, 2, 1] => 5,
        [3, 1, 1] => 4,
        [3, 2] => 3,
        [4, 1] => 2,
        [5] => 1,
        _ => unreachable!()

    };

    let mut card = 0;
    for b in buckets {
        for _i in 0..b.1 {
            hand[card] = b.0;
            card += 1;
        }
    }

    return (hand.to_vec(), hand_type);
}

fn get_hand_type_joker(hand: &mut Vec<usize>) -> (Vec<usize>, usize) {
    let mut no_jokes_lmao : Vec<usize> = hand.iter().filter(|n| **n != 1).cloned().collect();
    let buckets = get_groups(&mut no_jokes_lmao);
    let mut col : Vec<_> = buckets.iter().map(|n| n.1).collect();
    let jokers : usize = hand.iter().filter(|n| **n == 1).sum();

    if col.is_empty() {
        col.push(5);
    } else {
        col[0] += jokers;
    }

    let hand_type = match col[..] {
        [1, 1, 1, 1, 1] => 7,
        [2, 1, 1, 1] => 6,
        [2, 2, 1] => 5,
        [3, 1, 1] => 4,
        [3, 2] => 3,
        [4, 1] => 2,
        [5] => 1,
        _ => unreachable!()

    };

    return (hand.to_vec(), hand_type);
}
fn part1(data: &str) -> usize {

    let m : HashMap<&str, usize> = HashMap::<&str, usize>::from([
        ("A", 14),
        ("K", 13),
        ("Q", 12),
        ("J", 11),
        ("T", 10),
        ("9", 9),
        ("8", 8),
        ("7", 7),
        ("6", 6),
        ("5", 5),
        ("4", 4),
        ("3", 3),
        ("2", 2),
    ]);

    let count = data.lines().count();
    let lines : Vec<_> = data.lines().map(|l| l.split_whitespace().collect::<Vec<_>>()).collect();


    let hands : Vec<_> = lines.iter()
        .map(|l| l.get(0).unwrap()
             .split("")
             .filter(|c| *c != "").collect::<Vec<_>>()
             .iter()
             .map(|&c| 
                  {
                      m.get(c).cloned().unwrap()
                  }
                )
             .collect::<Vec<_>>()).collect::<Vec<_>>();

    let bids : Vec<_> = lines.iter().map(|l| l.get(1).unwrap().parse::<usize>().unwrap()).collect();

    let mut sorted : Vec<(Vec<usize>, usize, usize)> = Default::default();

    for (i, h) in hands.iter().enumerate() {
        let (s, ht) = get_hand_type(&mut h.to_owned());
        sorted.push((h.to_vec(), ht, bids[i]));
    }
    sorted.sort_unstable_by(|h1, h2|  {
                    let mut r1 = h2.1.cmp(&h1.1);
                    if r1.is_eq() {
                        for i in 0..h1.0.len() {
                            r1 = h1.0[i].cmp(&h2.0[i]);
                            if r1.is_eq() {
                                continue
                            } else {
                                break;
                            }
                        }    
                    }
                    return r1;
    }
    );

    let mut result = 0;
    for i in 0..sorted.len() {
        result += (i + 1) * sorted[i].2;
    }

    return result;
}

fn part2(data: &str) -> usize {
    let m : HashMap<&str, usize> = HashMap::<&str, usize>::from([
        ("A", 14),
        ("K", 13),
        ("Q", 12),
        ("T", 10),
        ("9", 9),
        ("8", 8),
        ("7", 7),
        ("6", 6),
        ("5", 5),
        ("4", 4),
        ("3", 3),
        ("2", 2),
        ("J", 1)
    ]);

    let lines : Vec<_> = data.lines().map(|l| l.split_whitespace().collect::<Vec<_>>()).collect();


    let hands : Vec<_> = lines.iter()
        .map(|l| l.get(0).unwrap()
             .split("")
             .filter(|c| *c != "").collect::<Vec<_>>()
             .iter()
             .map(|&c| 
                  {
                      m.get(c).cloned().unwrap()
                  }
                )
             .collect::<Vec<_>>()).collect::<Vec<_>>();

    let bids : Vec<_> = lines.iter().map(|l| l.get(1).unwrap().parse::<usize>().unwrap()).collect();

    let mut sorted : Vec<(Vec<usize>, usize, usize)> = Default::default();
    for (i, h) in hands.iter().enumerate() {
        let (s, ht) = get_hand_type_joker(&mut h.to_owned());
        sorted.push((h.to_vec(), ht, bids[i]));
    }

    sorted.sort_unstable_by(|h1, h2|  {
                    let mut r1 = h2.1.cmp(&h1.1);
                    if r1.is_eq() {
                        for i in 0..h1.0.len() {
                            r1 = h1.0[i].cmp(&h2.0[i]);
                            if r1.is_eq() {
                                continue
                            } else {
                                break;
                            }
                        }    
                    }
                    return r1;
    }
    );
    let mut result = 0;
    for i in 0..sorted.len() {
        result += (i + 1) * sorted[i].2;
    }
    return result;

}

#[test]
fn t_part1() {
    assert_eq!(part1("32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483"), 6440);
}

#[test]
fn t_part2() {
    assert_eq!(part2("32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483"), 5905);
}

fn main() {

    let content = std::fs::read_to_string("../data.txt").expect("Unable to read input data");

    println!("Silver: {}", part1(&content));
    println!("Gold {}", part2(&content));
}
