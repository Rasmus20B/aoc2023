
import Data.Char
import Data.List.Split

values = [
("one", 1), 
("two", 2), 
("three", 3), 
("four", 4), 
("five", 5), 
("six", 6), 
("seven", 7), 
("eight", 8), 
("nine", 9)
]

getDigits :: String -> String
getDigits = filter isDigit

digsToInts :: String -> [Int]
digsToInts = map digitToInt

fromDigs = foldl addDigit 0 
  where addDigit num d = 10 * num + d

getFirstAndLastInt :: String -> Int 
getFirstAndLastInt s = fromDigs $ digsToInts $ [head $ getDigits s] ++ [last $ getDigits s]

part1 :: String -> Int
part1 s = sum $ map (getFirstAndLastInt) (lines s)

part2 :: String -> Int 
part2 s = sum $ map splitOn (lines s)


main :: IO ()
main = do 
  content <- readFile "data"
  putStrLn $ show . part1 $ content
  putStrLn $ show . part2 $ content

