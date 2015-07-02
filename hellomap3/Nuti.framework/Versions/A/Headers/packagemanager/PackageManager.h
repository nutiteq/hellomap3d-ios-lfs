/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_PACKAGEMANAGER_H_
#define _NUTI_PACKAGEMANAGER_H_

#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>

#include "PackageInfo.h"
#include "PackageMetaInfo.h"
#include "PackageStatus.h"
#include "PackageTileMask.h"
#include "PackageManagerListener.h"

namespace sqlite3pp {
	class database;
	namespace ext {
		class function;
	}
}

namespace Nuti {
	/**
	 * Base class for offline map package manager. Package manager supports downloading/removing packages.
	 * It can be queried about available packages and status of the packages. It works asynchronously in
	 * the background and can inform app when packages have been updated.
	 * It works persistently. If a package download is started and app is closed, the download will resume
	 * when the package manager is started next time.
	 */
	class PackageManager {
	public:
		/**
		 * Logger interface.
		 */
		class Logger {
		public:
			virtual ~Logger() = default;

			virtual void info(const std::string& msg) = 0;
			virtual void error(const std::string& msg) = 0;
		};

		/**
		 * Listener interface for package change events.
		 */
		class OnChangeListener {
		public:
			virtual ~OnChangeListener() = default;

			virtual void onTilesChanged() = 0;
		};

		/**
		 * Constructs a new package manager, given URL for package list and data folder.
		 * The data folder must exist before creating a new package manager and it is assumed to be persistent.
		 * Note: the package manager must be explicitly started using start() method!
		 * @param packageListUrl The URL that defines all packages.
		 * @param dataFolder The folder where downloaded packages are kept. It must exist and must be writable.
		 * @param serverEncKey Encryption key for server packages
		 * @param localEncKey Encryption key for local packages
		 * @param logger The logger instance to use for reporting events.
		 */
		PackageManager(const std::string& packageListUrl, const std::string& dataFolder, const std::string& serverEncKey, const std::string& localEncKey, const std::shared_ptr<Logger>& logger);
		virtual ~PackageManager();

		/**
		 * Returns the current listener for package manager events.
		 * @return The current listener or null if none is set.
		 */
		std::shared_ptr<PackageManagerListener> getPackageManagerListener() const;
		/**
		 * Sets the package manager listener.
		 * @param listener The new package manager listener to use.
		 */
		void setPackageManagerListener(const std::shared_ptr<PackageManagerListener>& listener);

		/**
		 * Registers listener for package data change events.
		 * @param listener The listener for change events.
		 */
		void registerOnChangeListener(const std::shared_ptr<OnChangeListener>& listener);
		/**
		 * Unregisters listener from package data change events.
		 * @param listener The previously added listener.
		 */
		void unregisterOnChangeListener(const std::shared_ptr<OnChangeListener>& listener);

		/**
		 * Starts the package manager. All previous tasks will be resumed after this.
		 * @return True if package manager was successfully started. False otherwise (can not create/access database).
		 */
		bool start();
		/**
		 * Stops the package manager. The stopping can be asynchronous or synchronous.
		 * @param wait If set to true, then synchronous stopping is performed and the operation may take a while.
		 */
		void stop(bool wait);

		/**
		 * Returns the tile at specified coordinates.
		 * @param zoom The zoom value of the tile to return.
		 * @param x The x coordinate of the tile to return.
		 * @param y The y coordinate of the tile to return.
		 * @return The corresponding tile data or null if tile was not found.
		 */
		std::shared_ptr<std::vector<unsigned char> > loadTile(int zoom, int x, int y) const;

		/**
		 * Returns the list of available server packages.
		 * Note that the list must be retrieved from the server first, using startPackageListDownload.
		 * @return The list of available server packages.
		 */
		std::vector<std::shared_ptr<PackageInfo> > getServerPackages() const;
		/**
		 * Returns the list of available local downloaded packages.
		 * @return The list of available local downloaded packages.
		 */
		std::vector<std::shared_ptr<PackageInfo> > getLocalPackages() const;
		/**
		 * Returns the metainfo of server packages.
		 * @return The metainfo data about server packages, or null if no metainfo is available.
		 */
		std::shared_ptr<PackageMetaInfo> getServerPackageListMetaInfo() const;
		/**
		 * Returns the age of server package list. This method can be used to measure the time of the download and check whether the list should be updated.
		 * @return The age of server package list in seconds.
		 */
		int getServerPackageListAge() const;

		/**
		 * Returns the specified server package.
		 * Note that the list must be retrieved from the server first, using startPackageListDownload.
		 * @return The specified server package or null if it is not in the server package list.
		 */
		std::shared_ptr<PackageInfo> getServerPackage(const std::string& packageId) const;
		/**
		 * Returns the specified local package.
		 * @return The specified local package or null if it can not be found in the package list.
		 */
		std::shared_ptr<PackageInfo> getLocalPackage(const std::string& packageId) const;
		/**
		 * Returns the status of the specified package.
		 * @param packageId The id of the package.
		 * @param version The version of the package. Use -1 for the latest version.
		 * @return The status of the package or null if it is not yet downloaded or downloading.
		 */
		std::shared_ptr<PackageStatus> getLocalPackageStatus(const std::string& packageId, int version) const;

		/**
		 * Starts downloading package list asynchronously. When this task finishes, listener is called and server package list is updated.
		 * @return True if the package list will be downloaded and listener will be notified (if set). False if it can not be downloaded.
		 */
		bool startPackageListDownload();
		/**
		 * Starts importing the specified package asynchronously. When this task finishes, listener is called and local package list is updated.
		 * Note 1: In general, package manager may need temporary storage equal to the size of the package during import. It is the responsibility of the app to perform such checks.
		 * Note 2: the package may not be deleted after this call, as the import is asynchronous operation. It is safe to delete the original file once import is complete (this is notified via manager listener).
		 * @param packageId The id of the package to download.
		 * @param version The version of the package.
		 * @param packageFileName The fully qualified path of the package.
		 * @return True is the package will be imported.
		 */
		bool startPackageImport(const std::string& packageId, int version, const std::string& packageFileName);
		/**
		 * Starts downloading specified package asynchronously. When this task finishes, listener is called and local package list is updated.
		 * Note: In general, package manager may need temporary storage equal to the size of the package during download. It is the responsibility of the app to perform such checks.
		 * @param packageId The id of the package to download.
		 * @return True is the package is available and will be downloaded. False if the package was not found.
		 */
		bool startPackageDownload(const std::string& packageId);
		/**
		 * Starts the removal of specified package asynchronously. When this task finishes, listener is called and local package list is updated.
		 * @param packageId The id of the package to remove.
		 * @return True is the package was found and will be removed. False if the package was not found.
		 */
		bool startPackageRemove(const std::string& packageId);

		/**
		 * Cancels the current/pending tasks involving of the specified package.
		 * @param packageId The id of the package to cancel
		 */
		void cancelPackageTasks(const std::string& packageId);

		/**
		 * Sets the priority of the specific package.
		 * If the given priority is higher than priority of any other package, other operations will be paused and this package is processed immediately.
		 * If the given priority is set to negative value, package download will be paused until priority is reset to non-negative value.
		 * @param packageId The id of the download package.
		 * @param priority The priority of the download package. If it is less than zero, package download is paused.
		 */
		void setPackagePriority(const std::string& packageId, int priority);
		
	protected:
		virtual std::string createLocalFilePath(const std::string& name) const;
		virtual std::string createPackageFileName(const std::string& packageId, int version) const;
		virtual std::string createPackageListUrl(const std::string& baseUrl) const;
		virtual std::string createPackageUrl(const std::string& packageId, int version, const std::string& baseUrl, bool downloaded) const;
		
		virtual std::shared_ptr<PackageInfo> getCustomPackage(const std::string& packageId, int version) const;
		
	private:
		struct Task {
			enum Command {
				NOP = 0,
				DOWNLOAD_PACKAGE_LIST = 1,
				DOWNLOAD_PACKAGE = 2,
				IMPORT_PACKAGE = 3,
				REMOVE_PACKAGE = 4
			};

			Command command = NOP;
			int priority = 0;
			PackageAction::PackageAction action = PackageAction::PACKAGE_ACTION_WAITING;
			int progress = 0;
			std::string packageId;
			int packageVersion = 0;
			std::string packageLocation;
		};

		struct PackageDatabase {
			std::string packageId;
			std::shared_ptr<sqlite3pp::database> packageDb;
			std::shared_ptr<sqlite3pp::ext::function> decryptFunc;
		};

		class PersistentTaskQueue {
		public:
			PersistentTaskQueue(const std::string& dbFileName);

			int getActiveTaskId(int currentActiveTaskId = -1) const;
			std::vector<int> getTaskIds() const;
			Task getTask(int taskId) const;

			int scheduleTask(const Task& task);
			bool isTaskCancelled(int taskId) const;
			void cancelTask(int taskId);
			void setTaskPriority(int taskId, int priority);
			void updateTaskStatus(int taskId, PackageAction::PackageAction action, float progress);
			void deleteTask(int taskId);

		private:
			std::shared_ptr<sqlite3pp::database> _localDb;
			mutable std::recursive_mutex _mutex;
		};

		struct PauseException : std::exception {
			PauseException() { }
		};

		struct CancelException : std::exception {
			CancelException() { }
		};
        
        struct PackageException : std::runtime_error {
            PackageException(PackageErrorType::PackageErrorType errorType, const std::string& msg) : runtime_error(msg), _errorType(errorType) { }
            PackageErrorType::PackageErrorType getErrorType() const { return _errorType; }
            
        private:
            PackageErrorType::PackageErrorType _errorType;
        };

		void run();

		bool downloadPackageList(int taskId);
		bool importPackage(int taskId);
		bool downloadPackage(int taskId);
		bool removePackage(int taskId);
		
		void syncLocalPackages();
		std::shared_ptr<sqlite3pp::database> getLocalPackageDb(const std::shared_ptr<PackageInfo>& packageInfo) const;
		void importLocalPackage(int id, const std::string& packageId, const std::string& packageFileName);
		void deleteLocalPackage(int id);

		bool isTaskCancelled(int taskId) const;
		bool isTaskPaused(int taskId) const;
		void updateTaskStatus(int taskId, PackageAction::PackageAction action, float progress);
		void setTaskFinished(int taskId);
		void setTaskPaused(int taskId);
		void setTaskCancelled(int taskId);
        void setTaskFailed(int taskId, PackageErrorType::PackageErrorType errorType);

		std::string loadPackageListJson(const std::string& jsonFileName) const;
		void savePackageListJson(const std::string& jsonFileName, const std::string& json) const;

		static void initializeDb(sqlite3pp::database& db, const std::string& encKey);
		static bool checkDbEncryption(sqlite3pp::database& db, const std::string& encKey);
		static void updateDbEncryption(sqlite3pp::database& db, const std::string& encKey);
		static std::string calculateDbKeyHash(const std::string& encKey);

		static void encryptTile(std::vector<unsigned char>& data, int zoom, int x, int y, const std::string& encKey);
		static void decryptTile(std::vector<unsigned char>& data, int zoom, int x, int y, const std::string& encKey);
		static void setCipherKeyIV(unsigned char* k, unsigned char* iv, int zoom, int x, int y, const std::string& encKey);

		static int downloadFile(const std::string& url, std::function<bool(const unsigned char*, std::size_t)> handler, std::uint64_t offset = 0);
		static bool inflateData(const std::vector<unsigned char>& in, std::vector<unsigned char>& out);

		const std::string _packageListUrl;
		const std::string _packageListFileName;
		const std::string _dataFolder;
		const std::string _serverEncKey;
		const std::string _localEncKey;
		const std::shared_ptr<Logger> _logger;
		mutable std::vector<PackageDatabase> _localPackageDbCache;
		mutable std::vector<std::shared_ptr<PackageInfo> > _serverPackageCache;
		std::vector<std::shared_ptr<PackageInfo> > _localPackages;
		std::shared_ptr<sqlite3pp::database> _localDb;
		std::shared_ptr<PersistentTaskQueue> _taskQueue;
		std::condition_variable_any _taskQueueCondition; // notified when new tasks are available
		std::shared_ptr<std::thread> _packageManagerThread;
		std::vector<std::shared_ptr<OnChangeListener> > _onChangeListeners;
		bool _stopped = true;
		int _prevTaskId = -1;
		PackageAction::PackageAction _prevAction = PackageAction::PACKAGE_ACTION_WAITING;
		int _prevRoundedProgress = 0;

		std::shared_ptr<PackageManagerListener> _packageManagerListener;
		mutable std::recursive_mutex _packageManagerListenerMutex;

		mutable std::recursive_mutex _mutex; // guards all state
	};
}

#endif
