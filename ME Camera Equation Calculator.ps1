# Data information
[int]$span = Read-Host -Prompt 'How many InterpDatas does the movement span?'
while ($span -lt 2) {
	$span = Read-Host -Prompt 'Please input an integer bigger than 1'
	$span
}
#@posStart = @()
#@posEnd = @()
#@rotStart = @()
#@rotEnd = @()
$span.GetType()

Read-Host -Prompt "Press Enter to exit"