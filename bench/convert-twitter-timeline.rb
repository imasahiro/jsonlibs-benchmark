open("./twitter.json") {|f|
    puts "["
    while l = f.gets
        puts l.strip + ","
    end
    puts "{}]"
}
