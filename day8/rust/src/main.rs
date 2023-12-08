use std::collections::HashMap;

fn gcd(mut a: usize, mut b: usize) -> usize {

    if a == b { return a};
    if b > a {
        let tmp = a;
        a = b;
        b = tmp;
    }
    while b>0 {
        let tmp = a;
        a = b;
        b = tmp%b;
    }
    return a;
}

fn build_graph(data: &str) -> Vec<Vec<usize>> {

    let mut split : Vec<_> = data.lines().skip(2).map(|l| l.split("=").collect::<Vec<_>>().iter().map(|s| s.trim()).collect::<Vec<_>>()).collect();
    let mut map : HashMap::<&str, usize> = Default::default();
    let mut alist : Vec<Vec<usize>> = Default::default();

    split.sort_by(|a, b| a[0..2].cmp(&b[0..2]));
    for (i, s) in split[0..].iter().enumerate() {

        let mut num = i;
        if s[0] == "ZZZ" {
            num = usize::MAX;
        }
        map.insert(s[0], num);
    }
    for s in split[0..].iter() {
        let forks = s[1].replace("(", "").replace(")", "");
        let fork : Vec<&str> = forks.split(",").map(|d| d.trim()).collect();

        let mut cur : Vec<usize> = Vec::new();
        for d in fork {
            cur.push(*map.get(d).unwrap());
        }

        alist.push(cur);
    }

    return alist;
}

fn part2(data: &str) -> usize {

    let lines : Vec<_> = data.lines().skip(2).map(|l| l.split("=").collect::<Vec<_>>().iter().map(|s| s.trim()).collect::<Vec<_>>()).collect();
    let mut spaces2 : HashMap<String, (String, String)> = Default::default();

    let lcm = |a:usize, b:usize| return a*(b/gcd(a, b));

    for l in lines {
        let mut latter = l[1].replace("(", "");
        latter = latter.replace(")", "");
        let dirs : Vec<_> = latter.trim().split(", ").collect::<Vec<_>>();
        spaces2.insert(l[0].to_owned(), (dirs[0].to_owned(), dirs[1].to_owned()));
    }

    let dirs : Vec<_> = data.lines().nth(0).unwrap().chars().map(|c| match c{
        'L' => 0,
        'R' => 1,
        _ => unreachable!()
    }).collect();
    let starts : Vec<_> = spaces2.iter().filter(|s| s.0.ends_with("A")).collect();
    let mut moves : Vec<usize> = Default::default();
    moves.resize(starts.len(), 0);

    for (i, s) in starts.iter().enumerate() {
        let mut pos = s.0;
        for d in dirs.iter().cycle() {
            if pos.ends_with("Z") {
                break;
            }
            let news = spaces2.get(pos).unwrap();
            match d {
                0 => pos = &news.0,
                1 => pos = &news.1,
                _ => unreachable!()
            }
            moves[i] += 1;
        }
    }

    let mut res = 1;
    for m in moves {
        res = lcm(res, m);
    }

    return res;
}
fn part1(data: &str) -> usize {

    let alist : Vec<Vec<usize>> =  build_graph(data); 
    let dirs : Vec<usize> = data.lines().nth(0).expect("unable to get first line").chars().map(|c| match c {
        'L' => 0,
        'R' => 1,
        _ => unreachable!()
    }).collect();

    let mut pos = 0;
    let mut moves = 0;

    for d in dirs.iter().cycle() {
        if pos == usize::MAX {
            return moves;
        }
        pos = alist[pos][*d];
        moves += 1;
    }
    return moves;
}

#[test]
fn t_part1() {
    assert_eq!(part1("RL

AAA = (BBB, CCC)
BBB = (DDD, EEE)
CCC = (ZZZ, GGG)
DDD = (DDD, DDD)
EEE = (EEE, EEE)
GGG = (GGG, GGG)
ZZZ = (ZZZ, ZZZ)"), 2);

}
#[test]
fn t_part1_cycle() {
    assert_eq!(part1("LLR

AAA = (BBB, BBB)
BBB = (AAA, ZZZ)
ZZZ = (ZZZ, ZZZ)"), 6);
}

#[test]
fn t_part2() {
    assert_eq!(part2("LR

11A = (11B, XXX)
11B = (XXX, 11Z)
11Z = (11B, XXX)
22A = (22B, XXX)
22B = (22C, 22C)
22C = (22Z, 22Z)
22Z = (22B, 22B)
XXX = (XXX, XXX)"), 6);
}

fn main() {

    let data = std::fs::read_to_string("../data.txt").expect("Unable to read file.");

    println!("Silver: {}", part1(&data));
    println!("Gold: {}", part2(&data));
}
