# Display the number of arguments
echo "Number of arguments: $#"

# Display each argument
for arg in "$@"; do
    echo "Argument: $arg"
done

git add *

git commit -m $1

git push

