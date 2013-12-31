/*
 * libchuck
 * Brian Sorahan 2014
 */

namespace chuck {
    class Chuck {
    public:

        virtual void Destroy() = 0;

        /*
         * Spork a shred from a file.
         * args[0] should be the filename,
         * the rest of the args will be command-line args to the file.
         * Returns true/false if the operation succeeds/fails.
         */
        virtual bool sporkFile(const char ** args) = 0;

    };

    /*
     * Create a new instance of Chuck
     */
    Chuck * Create(int port);
}
