
fn part1(data: &str) -> i64{

    let seqs = data.lines();
    let mut result = 0;

    let mut tmp : Vec<Vec<i64>> = Default::default();
    for s in seqs {
        let mut it = 0;
        let nums = s.split(" ").map(|n| n.parse::<i64>().unwrap()).collect::<Vec<i64>>(); 
        tmp.push(nums);
        let mut tot : i64 = tmp[0].iter().sum();
        it += 1;
        while tot != 0 {
            let mut new = Vec::new();
            for a in tmp[it-1].windows(2) {
                new.push(a[1] - a[0]);
            }
            tot = new.iter().sum();
            it += 1;
            tmp.push(new);
        }

        it -= 1;
        tmp[it].push(0);

        while it > 0 {
            it -= 1;
            let next = tmp[it+1].last().unwrap() + tmp[it][tmp[it].len() - 1];
            tmp[it].push(next);
        }
        result += tmp[0].last().unwrap();
        tmp.clear();
    }

    return result;
}

fn part2(data: &str) -> i64 {

    let seqs = data.lines();
    let mut result = 0;

    let mut tmp :Vec<Vec<i64>> = Default::default();

    for s in seqs {
        let mut it = 0;
        let nums = s.split(" ").map(|n| n.parse::<i64>().unwrap()).collect::<Vec<i64>>(); 

        tmp.push(nums);
        let mut tot : i64 = tmp[0].iter().sum();
        it += 1;
        
        while tot != 0 {
            let mut new = Vec::new();
            for a in tmp[it-1].windows(2) {
                new.push(a[1] - a[0]);
            }
            tot = new.iter().sum();
            it += 1;
            tmp.push(new);
        }

        it -= 1;
        tmp[it].insert(0, 0);
        while it > 0 {
            it -= 1;
            let next = tmp[it][0] - tmp[it+1].first().unwrap();
            tmp[it].insert(0, next);
        }
        result += tmp[0].first().unwrap();
        tmp.clear();
    }

    return result;
}

#[test]
fn t_part1() {
    assert_eq!(part1("0 3 6 9 12 15
1 3 6 10 15 21
10 13 16 21 30 45"), 114);
}
#[test]
fn t_part2() {
    assert_eq!(part2("0 3 6 9 12 15
1 3 6 10 15 21
10 13 16 21 30 45"), 2);
}

fn main() {

    let content = std::fs::read_to_string("../data.txt").expect("Unable to read file.");

    println!("Silver: {}", part1(&content));
    println!("Gold: {}", part2(&content));
}


