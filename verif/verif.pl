#!/usr/bin/perl

# Purpose: Verify if the counters read in are in sequential order.

my $numChars;
my @split;
my $splitCounter = 0;
my $readInNum;

if ( @ARGV != 2 ) {
    print "Usage: <file> <counter start>\n";
    exit(1);
}   

open IN, $ARGV[0] || die "Can\'t open file $ARGV[0]\n";

my $counter = $ARGV[1];

sub getNumChars {
    my ($num) = @_;

    my $ret = 0;
    do {
        $num = $num / 10;
        $ret += 1;
    } while ($num >= 1);
    return $ret;
}

sub readNums {
    do {   
        $numChars = getNumChars($counter);
        $readInNum = "";
        while ( $numChars > 0 ) {
            $readInNum .= $split[$splitCounter];
            $splitCounter = $splitCounter + 1;
            $numChars = $numChars - 1;
        }
        if ( $counter != int($readInNum)) {
            print "Error: ($counter) != ($readInNum)\n";
            exit(1);
            last;
        }
        $counter = $counter + 1;
    } while ($splitCounter < (scalar @split))
}

while (<IN>) {
    chomp $_;
    @split = split //, $_;
    $splitCounter = 0;
    readNums();
}

close IN;
