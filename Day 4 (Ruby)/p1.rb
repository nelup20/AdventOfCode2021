
numbers = File.read('numbers.txt').split(',').map(&:to_i)

boards = File.read('boards.txt').split("\n")
boards.delete_if { |x| x == '' }
boards = boards.map { |x| x.split(' ').map(&:to_i) }
boards = boards.each_slice(5).entries

def bingo?(board_to_check)
  row_nil = 0
  col_nil = 0

  (0..4).each do |i|
    (0..4).each do |j|
      row_nil += 1 if board_to_check[i][j].nil?

      col_nil += 1 if board_to_check[j][i].nil?
    end

    return true if row_nil == 5 || col_nil == 5

    row_nil = 0
    col_nil = 0
  end

  false
end

def mark_board(board, number)
  board.each { |row| row.map! { |num| num == number ? nil : num } }
end

def find_winning_board(numbers, boards)
  (0..numbers.length - 1).each do |i|
    (0..boards.length - 1).each do |j|
      mark_board(boards[j], numbers[i])

      return [boards[j], numbers[i]] if bingo?(boards[j])
    end
  end
end

winning_board, last_number = find_winning_board(numbers, boards)
result = 0

winning_board.each { |row| row.each { |num| result += num unless num.nil? } }

result *= last_number

puts "Final result: #{result}"



