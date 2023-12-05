
fn map_seeds_to_range(seeds: Vec<usize>, ds: usize, ss: usize, len: usize) -> Vec<usize> {

    seeds
        .into_iter()
        .map(|s| 
            if (ss..=ss+len-1).contains(&s) {
                let offset = s - ss;
                return offset + ds;
            } else {
                return s;
            }
        ).collect()
}

fn part1(data: &str) -> usize {

    let categories : Vec<_> = data.split("\n\n").map(|c| c.lines().collect::<Vec<_>>()).collect();

    let mut seeds : Vec<_> = categories[0][0]
        .split(" ")
        .skip(1)
        .map(|n| n.parse::<usize>().unwrap())
        .collect();

    let maps : Vec<_> = categories
        .into_iter()
        .map(|l| l.get(1..).unwrap()
             .into_iter()
             .map(|r| 
                  {
                  r
                  .split(" ")
                  .map(|n| n.parse::<usize>().unwrap()).collect::<Vec<_>>()
                  }
                  )
             .collect::<Vec<_>>()).collect();

    for m in maps {
        for s in &mut seeds {
            for line in &m {
                let ds = line[0];
                let ss = line[1];
                let len = line[2];
                if (ss..ss+len).contains(&s) {
                    *s = *s - ss + ds;
                    break;
                }
            }
        }
    }
    return *seeds.iter().min().unwrap();
}

fn part2(data: &str) -> usize{

    let categories : Vec<_> = data.split("\n\n").map(|c| c.lines().collect::<Vec<_>>()).collect();

    let mut seeds_ranges : Vec<_> = categories[0][0]
        .split(" ")
        .skip(1)
        .map(|n| n.parse::<usize>().unwrap())
        .into_iter()
        .collect();

    let seed_range_pairs = seeds_ranges.chunks(2);

    let maps : Vec<_> = categories
        .into_iter()
        .map(|l| l.get(1..).unwrap()
             .into_iter()
             .map(|r| 
                  {
                  r
                  .split(" ")
                  .map(|n| n.parse::<usize>().unwrap()).collect::<Vec<_>>()
                  }
                  )
             .collect::<Vec<_>>()).collect();

    let mut min = usize::MAX;

    for s in seed_range_pairs {
        let mut seeds : Vec<usize> = (s[0]..s[0]+s[1]).collect();

        // println!("looking at range: {:?}", seeds);
        for m in &maps {
            for seed in &mut seeds  {
                for line in m {
                    let ds = line[0];
                    let ss = line[1];
                    let len = line[2];
                    if (ss..ss+len).contains(&seed) {
                        *seed = *seed - ss + ds;
                        break;
                    }
                }
            }

        }

        min = min.min(*seeds.iter().min().unwrap());

    }

    return min;

}

#[test]
fn t_part2() {
    assert_eq!(part2("seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4"), 46);
}
#[test]
fn t_part1() {
    assert_eq!(part1("seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4"), 35);
}

fn main() {

    let content = std::fs::read_to_string("../data.txt").expect("Unable to read file");

    println!("Part 1: {}", part1(&content));
    println!("Part 2: {}", part2(&content));

}
