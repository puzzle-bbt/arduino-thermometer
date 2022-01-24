/**
 * A synchron function example.
 * @param name the name of the person
 * @return {`Hello ${string}`} the hello message
 */
exports.sayHello = (name) => {
    console.log('say hello to ', name);
    return `Hello ${name}`;
}

/**
 * A asynchron function example.
 * @param timeRange the time range like day, week or month
 * @return {Promise<string>} the congratulation message
 */
exports.sayHelloAsync = async (timeRange) => {
    return `I wish you a nice ${timeRange}.`
}