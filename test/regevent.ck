RegEvent re;
1 => re.intval;
3.14 => re.floatval;
"foo" => re.stringval;

function void and_beans() {
    500::ms => now;
    "bar" => re.stringval;
    re.signal();
}

spork ~ and_beans();
re => now;
